/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Common.h"
#include "InstrumentEditor.h"

#include "PageBackgroundA.h"

#include "InstrumentEditorPin.h"
#include "InstrumentComponent.h"
#include "InstrumentEditorConnector.h"
#include "InstrumentNodeSelectionMenu.h"
#include "HeadlineContextMenuController.h"

#include "AudioCore.h"
#include "MainLayout.h"

static const AudioProcessorGraph::NodeID idZero;

InstrumentEditor::InstrumentEditor(WeakReference<Instrument> instrument,
    WeakReference<AudioCore> audioCore) :
    instrument(instrument),
    audioCore(audioCore)
{
    this->background = make<PageBackgroundA>();
    this->addAndMakeVisible(this->background.get());

    this->contextMenuController = make<HeadlineContextMenuController>(*this);

    this->instrument->addChangeListener(this);
    this->audioCore->getDevice().addChangeListener(this);
    
    this->setOpaque(true);
    
    this->setWantsKeyboardFocus(false);
    this->setFocusContainerType(Component::FocusContainerType::none);
}

InstrumentEditor::~InstrumentEditor()
{
    this->audioCore->getDevice().removeChangeListener(this);

    if (this->instrument != nullptr)
    {
        this->instrument->removeChangeListener(this);
    }
    
    this->draggingConnector = nullptr;
    this->background = nullptr;
    this->deleteAllChildren();
}

void InstrumentEditor::mouseDown(const MouseEvent &e)
{
    this->deselectAllNodes();
}

void InstrumentEditor::resized()
{
    this->background->setBounds(0, 0, this->getWidth(), this->getHeight());
    this->updateComponents();
}

void InstrumentEditor::changeListenerCallback(ChangeBroadcaster *)
{
    this->updateComponents();
}

InstrumentComponent *InstrumentEditor::getComponentForNode(AudioProcessorGraph::NodeID id) const
{
    for (int i = this->getNumChildComponents(); --i >= 0;)
    {
        if (auto *fc = dynamic_cast<InstrumentComponent *>(this->getChildComponent(i)))
        {
            if (fc->nodeId == id)
            {
                return fc;
            }
        }
    }
    
    return nullptr;
} 

InstrumentEditorConnector *InstrumentEditor::getComponentForConnection(AudioProcessorGraph::Connection conn) const
{
    for (int i = this->getNumChildComponents(); --i >= 0;)
    {
        if (auto *c = dynamic_cast<InstrumentEditorConnector *>(this->getChildComponent(i)))
        {
            if (c->connection == conn)
            {
                return c;
            }
        }
    }
    
    return nullptr;
}

InstrumentEditorPin *InstrumentEditor::findPinAt(const int x, const int y) const
{
    for (int i = this->getNumChildComponents(); --i >= 0;)
    {
        if (auto *fc = dynamic_cast<InstrumentComponent *>(this->getChildComponent(i)))
        {
            if (auto *pin = dynamic_cast<InstrumentEditorPin *>(fc->getComponentAt(x - fc->getX(), y - fc->getY())))
            {
                return pin;
            }
        }
    }
    
    return nullptr;
}

void InstrumentEditor::deselectAllNodes()
{
    this->selectedNode = idZero;
    
    for (int i = this->getNumChildComponents(); --i >= 0;)
    {
        if (auto *node = dynamic_cast<InstrumentComponent *>(this->getChildComponent(i)))
        {
            node->setSelected(false);
        }
    }

    App::Layout().hideSelectionMenu();
}

void InstrumentEditor::selectNode(AudioProcessorGraph::NodeID id, const MouseEvent &e)
{
    if (e.mods.isRightButtonDown())
    {
        this->selectedNode = id;
    }
    else
    {
        // any other event than right-click toggles the selection:
        this->selectedNode = (this->selectedNode == id) ? idZero : id;
    }

    for (int i = this->getNumChildComponents(); --i >= 0;)
    {
        if (auto *node = dynamic_cast<InstrumentComponent *>(this->getChildComponent(i)))
        {
            node->setSelected(node->nodeId == this->selectedNode);
        }
    }

    App::Layout().hideSelectionMenu();

    if (this->selectedNode != idZero)
    {
        App::Layout().showSelectionMenu(this);

        if (e.mods.isRightButtonDown())
        {
            this->contextMenuController->showMenu(e);
        }
    }
}

void InstrumentEditor::updateComponents()
{
    this->deselectAllNodes();

    for (int i = this->getNumChildComponents(); --i >= 0;)
    {
        if (auto *fc = dynamic_cast<InstrumentComponent *>(getChildComponent(i)))
        {
            fc->update();
        }
    }
    
    for (int i = this->getNumChildComponents(); --i >= 0;)
    {
        auto *cc = dynamic_cast<InstrumentEditorConnector *>(getChildComponent(i));
        if (cc != nullptr && cc != this->draggingConnector.get())
        {
            if (! instrument->isConnected(cc->connection))
            {
                delete cc;
            }
            else
            {
                cc->update();
            }
        }
    }
    
    for (int i = instrument->getNumNodes(); --i >= 0;)
    {
        const AudioProcessorGraph::Node::Ptr f(instrument->getNode(i));
        if (this->getComponentForNode(f->nodeID) == nullptr)
        {
            auto *comp = new InstrumentComponent(instrument, f->nodeID);
            this->addAndMakeVisible(comp);
            comp->update();
        }
    }
    
    const auto &connections = instrument->getConnections();
    const int numConnections = int(connections.size());
    for (int i = numConnections; --i >= 0;)
    {
        AudioProcessorGraph::Connection c = connections.at(i);
        if (this->getComponentForConnection(c) == nullptr)
        {
            auto *comp = new InstrumentEditorConnector(instrument);
            this->addAndMakeVisible(comp);
            comp->setInput(c.source);
            comp->setOutput(c.destination);
        }
    }
}

//===----------------------------------------------------------------------===//
// Dragging
//===----------------------------------------------------------------------===//

void InstrumentEditor::beginConnectorDrag(
    AudioProcessorGraph::NodeID sourceID, int sourceChannel,
    AudioProcessorGraph::NodeID destinationID, int destinationChannel,
    const MouseEvent &e)
{
    this->draggingConnector.reset(dynamic_cast<InstrumentEditorConnector *>(e.originalComponent));
    if (this->draggingConnector == nullptr)
    {
        this->draggingConnector = make<InstrumentEditorConnector>(instrument);
    }
    
    AudioProcessorGraph::NodeAndChannel source;
    source.nodeID = sourceID;
    source.channelIndex = sourceChannel;

    AudioProcessorGraph::NodeAndChannel destination;
    destination.nodeID = destinationID;
    destination.channelIndex = destinationChannel;

    this->draggingConnector->setInput(source);
    this->draggingConnector->setOutput(destination);
    
    this->addAndMakeVisible(this->draggingConnector.get());
    this->draggingConnector->toFront(false);
    
    this->dragConnector(e);
}

void InstrumentEditor::dragConnector(const MouseEvent &e)
{
    const auto e2 = e.getEventRelativeTo(this);
    if (this->draggingConnector != nullptr)
    {
        this->draggingConnector->setTooltip({});
        
        int x = e2.x;
        int y = e2.y;
        
        if (auto pin = this->findPinAt(x, y))
        {
            auto c = this->draggingConnector->connection;
            
            if (c.source.nodeID == idZero && !pin->isInput)
            {
                c.source.nodeID = pin->nodeID;
                c.source.channelIndex = pin->index;
            }
            else if (c.destination.nodeID == idZero && pin->isInput)
            {
                c.destination.nodeID = pin->nodeID;
                c.destination.channelIndex = pin->index;
            }
            
            if (instrument->canConnect(c))
            {
                x = pin->getParentComponent()->getX() + pin->getX() + pin->getWidth() / 2;
                y = pin->getParentComponent()->getY() + pin->getY() + pin->getHeight() / 2;
                
                this->draggingConnector->setTooltip(pin->getTooltip());
            }
        }
        
        if (this->draggingConnector->connection.source.nodeID == idZero)
        {
            this->draggingConnector->dragStart(x, y);
        }
        else
        {
            this->draggingConnector->dragEnd(x, y);
        }
    }
}

void InstrumentEditor::endDraggingConnector(const MouseEvent &e)
{
    if (this->draggingConnector == nullptr)
    {
        return;
    }
    
    this->draggingConnector->setTooltip({});
    
    const auto e2 = e.getEventRelativeTo(this);
    
    const auto c = this->draggingConnector->connection;
    auto srcNode = c.source.nodeID;
    auto srcChannel = c.source.channelIndex;
    auto dstNode = c.destination.nodeID;
    auto dstChannel = c.destination.channelIndex;
    
    this->fader.fadeOut(this->draggingConnector.get(), Globals::UI::fadeOutLong);
    this->draggingConnector = nullptr;
    
    if (auto pin = findPinAt(e2.x, e2.y))
    {
        if (srcNode == idZero)
        {
            if (pin->isInput)
            { return; }
            
            srcNode = pin->nodeID;
            srcChannel = pin->index;
        }
        else
        {
            if (! pin->isInput)
            { return; }
            
            dstNode = pin->nodeID;
            dstChannel = pin->index;
        }
        
        instrument->addConnection(srcNode, srcChannel, dstNode, dstChannel);
    }
}

//===----------------------------------------------------------------------===//
// HeadlineItemDataSource
//===----------------------------------------------------------------------===//

bool InstrumentEditor::hasMenu() const noexcept { return true; }
bool InstrumentEditor::canBeSelectedAsMenuItem() const { return false; }

UniquePointer<Component> InstrumentEditor::createMenu()
{
    return make<InstrumentNodeSelectionMenu>(*this->instrument.get(),
        this->instrument->getNodeForId(this->selectedNode));
}

Image InstrumentEditor::getIcon() const
{
    return Icons::findByName(Icons::audioPlugin, Globals::UI::headlineIconSize);
}

String InstrumentEditor::getName() const
{
    const auto node = this->instrument->getNodeForId(this->selectedNode);
    jassert(node);

    if (auto plugin = dynamic_cast<AudioPluginInstance *>(node->getProcessor()))
    {
        return plugin->getName();
    }

    return {};
}
