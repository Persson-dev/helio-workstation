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
#include "CutPointMark.h"
#include "ClipComponent.h"
#include "HelioTheme.h"

static inline ComponentAnimator &rootAnimator()
{
    return Desktop::getInstance().getAnimator();
}

CutPointMark::CutPointMark(SafePointer<Component> targetComponent, float absPosX) :
    targetComponent(targetComponent),
    absPosX(absPosX)
{
    this->setAlpha(0.f);
    this->setPaintingIsUnclipped(true);
    this->setWantsKeyboardFocus(false);
    this->setInterceptsMouseClicks(false, false);
}

CutPointMark::~CutPointMark()
{
    rootAnimator().cancelAnimation(this, false);
    if (this->initialized)
    {
        rootAnimator().animateComponent(this,this->getBounds(), 0.f,
            Globals::UI::fadeOutShort, true, 0.0, 0.0);
    }
}

void CutPointMark::fadeIn()
{
    rootAnimator().animateComponent(this,
        this->getBounds(), 1.f, Globals::UI::fadeInShort, false, 0.0, 0.0);
}

void CutPointMark::updateBounds(bool forceNoAnimation)
{
    rootAnimator().cancelAnimation(this, false);

    if (this->absPosX <= 0.f || this->absPosX >= 1.f)
    {
        if (this->initialized)
        {
            this->setVisible(false);
            this->initialized = false;
        }
    }
    else if (this->targetComponent != nullptr)
    {
        const float wt = float(this->targetComponent->getWidth());
        const int ht = this->targetComponent->getHeight();
        const int x = this->targetComponent->getX() + int(wt * this->absPosX);
        const int y = this->targetComponent->getY();
        const Rectangle<int> newBounds(x - 2, y, 5, ht);

        if (!this->initialized || forceNoAnimation)
        {
            this->initialized = true;
            this->setVisible(true);
            this->setBounds(newBounds);
        }
        else
        {
            rootAnimator().animateComponent(this, newBounds, 1.f, 20, false, 1.0, 0.0);
        }
    }
}

void CutPointMark::updatePosition(float pos)
{
    this->absPosX = pos;
    this->updateBounds();
}

Component *CutPointMark::getComponent() const noexcept
{
    return this->targetComponent.getComponent();
}

float CutPointMark::getCutPosition() const noexcept
{
    return this->absPosX;
}

//===----------------------------------------------------------------------===//
// For the piano roll
//===----------------------------------------------------------------------===//

NoteCutPointMark::NoteCutPointMark(SafePointer<Component> targetComponent, float absPosX) :
    CutPointMark(targetComponent, absPosX) {}

void NoteCutPointMark::paint(Graphics &g)
{
    const auto w = float(this->getWidth());
    const auto h = float(this->getHeight());

    g.setColour(Colours::white.withAlpha(0.25f));
    g.fillRect(w / 2.f - 1.5f, 1.f, 3.f, h - 2.f);
    //g.fillRect(w / 2.f - 1.f, 1.f, 2.f, h - 2.f);

    g.setColour(Colours::black.withAlpha(0.9f));
    g.fillRect(w / 2.f - 0.75f, 1.f, 1.5f, h - 2.f);
    //g.fillRect(w / 2.f - 0.5f, 1.f, 1.f, h - 2.f);

    Path p;
    p.addTriangle(0.f, 0.f, w, 0.f, w / 2.f, 2.f);
    g.fillPath(p);

    p.clear();
    p.addTriangle(0.f, h, w, h, w / 2.f, h - 2.f);
    g.fillPath(p);
}

//===----------------------------------------------------------------------===//
// For the pattern roll
//===----------------------------------------------------------------------===//

ClipCutPointMark::ClipCutPointMark(SafePointer<ClipComponent> targetComponent) :
    CutPointMark(static_cast<Component *>(targetComponent.getComponent()), 0.f),
    colour(targetComponent->getClip().getTrackColour().interpolatedWith(Colours::white, 0.5f)) {}

void ClipCutPointMark::paint(Graphics &g)
{
    const auto w = this->getWidth();
    const auto h = this->getHeight();

    g.setColour(Colours::black.withAlpha(0.3f));
    g.fillRect(w / 2 - 1, 2, 3, this->getHeight() - 3);

    g.setColour(this->colour.withAlpha(0.75f));
    HelioTheme::drawDashedVerticalLine(g,
        2.f, 1.f,
        float(this->getHeight() - 2),
        3.f);

    g.fillRect(w / 2 - 1, 1, 3, 1);
    g.fillRect(w / 2 - 1, this->getHeight() - 1, 3, 1);
}

void ClipCutPointMark::updatePositionFromMouseEvent(int mouseX, int mouseY)
{
    if (mouseY < this->targetComponent->getY() ||
        mouseY > this->targetComponent->getBottom())
    {
        this->absPosX = -1.f;
    }
    else
    {
        this->absPosX = jlimit(0.f, 1.f,
            float(mouseX - this->targetComponent->getX()) /
            float(this->targetComponent->getWidth()));
    }

    this->updateBounds();
}
