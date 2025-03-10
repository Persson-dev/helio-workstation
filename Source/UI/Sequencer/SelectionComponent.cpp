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
#include "Lasso.h"
#include "SelectionComponent.h"
#include "HelioTheme.h"
#include "ColourIDs.h"

SelectionComponent::SelectionComponent() :
    fill(findDefaultColour(ColourIDs::SelectionComponent::fill)),
    outline(findDefaultColour(ColourIDs::SelectionComponent::outline)),
    currentFill(fill),
    currentOutline(outline)
{
    this->setSize(0, 0);
    this->setWantsKeyboardFocus(false);
    this->setInterceptsMouseClicks(false, false);
}

void SelectionComponent::beginLasso(const Point<float> &position,
    LassoSource<SelectableComponent *> *lassoSource)
{
    jassert(lassoSource != nullptr);
    jassert(this->getParentComponent() != nullptr);

    if (lassoSource != nullptr)
    {
        this->source = lassoSource;
        this->originalSelection = lassoSource->getLassoSelection().getItemArray();
        this->setSize(0, 0);
        this->toFront(false);
        this->startPosition = position.toDouble() / this->getParentSize();
        this->endPosition = this->startPosition;
        this->fadeIn();
    }
}

void SelectionComponent::dragLasso(const MouseEvent &e)
{
    if (this->source != nullptr)
    {
        this->endPosition = e.position.toDouble() / this->getParentSize();

        this->updateBounds();

        this->itemsInLasso.clearQuick();
        this->source->findLassoItemsInArea(this->itemsInLasso, this->getBounds());

        if (e.mods.isShiftDown())
        {
            this->itemsInLasso.removeValuesIn(this->originalSelection);
            this->itemsInLasso.addArray(this->originalSelection);
        }
        else if (e.mods.isAltDown())
        {
            this->originalSelection.removeValuesIn(this->itemsInLasso);
            this->itemsInLasso = this->originalSelection;
        }

        this->source->getLassoSelection() = Lasso(this->itemsInLasso);
    }
}

void SelectionComponent::updateBounds()
{
    const auto parentSize(this->getParentSize());
    const auto start = (this->startPosition * parentSize).toInt();
    const auto end = (this->endPosition * parentSize).toInt();
    this->setBounds({ start, end });
}

void SelectionComponent::endLasso()
{
    if (this->source != nullptr)
    {
        this->source = nullptr;
        this->originalSelection.clear();
        this->fadeOut();
    }
}

bool SelectionComponent::isDragging() const
{
    return this->source != nullptr;
}

void SelectionComponent::paint(Graphics &g)
{
    g.setColour(this->currentFill);
    g.fillRect(this->getLocalBounds());

    g.setColour(this->currentOutline);
    HelioTheme::drawDashedFrame(g, this->getLocalBounds());
}

const Point<double> SelectionComponent::getParentSize() const
{
    if (const auto *p = this->getParentComponent())
    {
        return { double(p->getWidth()), double(p->getHeight()) };
    }

    return { 1.0, 1.0 };
}

void SelectionComponent::timerCallback()
{
    const auto newOutline = this->currentOutline.interpolatedWith(this->targetOutline, 0.5f);
    const auto newFill = this->currentFill.interpolatedWith(this->targetFill, 0.3f);

    if (this->currentOutline == newOutline && this->currentFill == newFill)
    {
        //DBG("--- stop timer");
        this->stopTimer();

        if (newOutline.getAlpha() == 0)
        {
            //DBG("--- set visible = false");
            this->setVisible(false);
        }
    }
    else
    {
        this->currentOutline = newOutline;
        this->currentFill = newFill;
        this->updateBounds();
        this->repaint();
    }
}

void SelectionComponent::fadeIn()
{
    this->targetFill = this->fill;
    this->targetOutline = this->outline;
    this->setVisible(true);
    this->startTimerHz(60);
}

void SelectionComponent::fadeOut()
{
    this->targetFill = Colours::transparentBlack;
    this->targetOutline = Colours::transparentBlack;
    this->startTimerHz(60);
}
