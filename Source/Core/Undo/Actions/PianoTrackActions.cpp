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
#include "PianoTrackActions.h"
#include "MidiTrackSource.h"
#include "PianoTrackTreeItem.h"
#include "SerializationKeys.h"

//===----------------------------------------------------------------------===//
// Insert
//===----------------------------------------------------------------------===//

PianoTrackInsertAction::PianoTrackInsertAction(MidiTrackSource &source,
    WeakReference<TreeItem> parentTreeItem) :
    UndoAction(source),
    parentTreeItem(parentTreeItem) {}

PianoTrackInsertAction::PianoTrackInsertAction(MidiTrackSource &source,
    WeakReference<TreeItem> parentTreeItem,
    ValueTree targetSerializedState,
    String targetXPath) :
    UndoAction(source),
    parentTreeItem(parentTreeItem),
    trackState(targetSerializedState),
    trackName(std::move(targetXPath)) {}

bool PianoTrackInsertAction::perform()
{
    MidiTrackTreeItem *track = new PianoTrackTreeItem("empty");
    this->parentTreeItem->addChildTreeItem(track);
    
    track->deserialize(this->trackState);

    this->trackId = track->getTrackId().toString();
    track->setTrackName(this->trackName, true);

    return true;
}

bool PianoTrackInsertAction::undo()
{
    if (PianoTrackTreeItem *treeItem =
        this->source.findTrackById<PianoTrackTreeItem>(this->trackId))
    {
        // here the item state should be the same as when it was created
        // so don't serialize anything again
        return this->parentTreeItem->deleteItem(treeItem);
    }
    
    return false;
}

int PianoTrackInsertAction::getSizeInUnits()
{
    return this->trackName.length();
}

ValueTree PianoTrackInsertAction::serialize() const
{
    ValueTree tree(Serialization::Undo::pianoTrackInsertAction);
    tree.setProperty(Serialization::Undo::xPath, this->trackName);
    tree.setProperty(Serialization::Undo::trackId, this->trackId);
    tree.appendChild(this->trackState.createCopy());
    return tree;
}

void PianoTrackInsertAction::deserialize(const ValueTree &tree)
{
    this->trackName = tree.getProperty(Serialization::Undo::xPath);
    this->trackId = tree.getProperty(Serialization::Undo::trackId);
    this->trackState = tree.getChild(0).createCopy();
}

void PianoTrackInsertAction::reset()
{
    this->trackName.clear();
    this->trackId.clear();
    this->trackState = {};
}

//===----------------------------------------------------------------------===//
// Remove
//===----------------------------------------------------------------------===//

PianoTrackRemoveAction::PianoTrackRemoveAction(MidiTrackSource &source,
    WeakReference<TreeItem> parentTreeItem) :
    UndoAction(source),
    parentTreeItem(parentTreeItem) {}

PianoTrackRemoveAction::PianoTrackRemoveAction(MidiTrackSource &source,
    WeakReference<TreeItem> parentTreeItem,
    String targetTrackId) :
    UndoAction(source),
    parentTreeItem(parentTreeItem),
    trackId(std::move(targetTrackId)),
    numEvents(0) {}

bool PianoTrackRemoveAction::perform()
{
    if (PianoTrackTreeItem *treeItem =
        this->source.findTrackById<PianoTrackTreeItem>(this->trackId))
    {
        this->numEvents = treeItem->getSequence()->size();
        this->serializedTreeItem = treeItem->serialize();
        this->trackName = treeItem->getTrackName();
        return this->parentTreeItem->deleteItem(treeItem);
    }
    
    return false;
}

bool PianoTrackRemoveAction::undo()
{
    if (this->serializedTreeItem.isValid())
    {
        MidiTrackTreeItem *track = new PianoTrackTreeItem("empty");
        this->parentTreeItem->addChildTreeItem(track);
        track->deserialize(this->serializedTreeItem);
        track->setTrackName(this->trackName, true);
        return true;
    }
    
    return false;
}

int PianoTrackRemoveAction::getSizeInUnits()
{
    if (this->serializedTreeItem.isValid())
    {
        return (this->numEvents * sizeof(MidiEvent));
    }
    
    return 1;
}

ValueTree PianoTrackRemoveAction::serialize() const
{
    ValueTree tree(Serialization::Undo::pianoTrackRemoveAction);
    tree.setProperty(Serialization::Undo::xPath, this->trackName);
    tree.setProperty(Serialization::Undo::trackId, this->trackId);
    tree.appendChild(this->serializedTreeItem.createCopy());
    return tree;
}

void PianoTrackRemoveAction::deserialize(const ValueTree &tree)
{
    this->trackName = tree.getProperty(Serialization::Undo::xPath);
    this->trackId = tree.getProperty(Serialization::Undo::trackId);
    this->serializedTreeItem = tree.getChild(0).createCopy();
}

void PianoTrackRemoveAction::reset()
{
    this->trackName.clear();
    this->trackId.clear();
    this->serializedTreeItem = {};
}
