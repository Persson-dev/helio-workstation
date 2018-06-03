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

#pragma once

#include "ClipComponent.h"
#include "AutomationEvent.h"
#include "ProjectListener.h"

class MidiSequence;
class HybridRoll;
class ProjectTreeItem;
class AutomationStepEventComponent;
class AutomationStepEventsConnector;

class AutomationStepsClipComponent final : public ClipComponent, public ProjectListener
{
public:

    AutomationStepsClipComponent(ProjectTreeItem &project, MidiSequence *sequence,
        HybridRoll &roll, const Clip &clip);

    ~AutomationStepsClipComponent() override;

    //===------------------------------------------------------------------===//
    // Component
    //===------------------------------------------------------------------===//

    void mouseDown(const MouseEvent &e) override;
    void resized() override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

    //===------------------------------------------------------------------===//
    // ProjectListener
    //===------------------------------------------------------------------===//

    void onChangeMidiEvent(const MidiEvent &oldEvent,
        const MidiEvent &newEvent) override;
    void onAddMidiEvent(const MidiEvent &event) override;
    void onRemoveMidiEvent(const MidiEvent &event) override;

    // TODO! As a part of `automation editors` story
    void onAddClip(const Clip &clip) override {}
    void onChangeClip(const Clip &oldClip, const Clip &newClip) override {}
    void onRemoveClip(const Clip &clip) override {}

    void onAddTrack(MidiTrack *const track) override;
    void onRemoveTrack(MidiTrack *const track) override;
    void onChangeTrackProperties(MidiTrack *const track) override;

    void onChangeProjectBeatRange(float firstBeat, float lastBeat) override {}
    void onChangeViewBeatRange(float firstBeat, float lastBeat) override {}
    void onReloadProjectContent(const Array<MidiTrack *> &tracks) override;

protected:

    void insertNewEventAt(const MouseEvent &e, bool shouldAddTriggeredEvent);
    void removeEventIfPossible(const AutomationEvent &e);

    float getBeatByXPosition(int x) const;

    AutomationStepEventComponent *getPreviousEventComponent(int indexOfSorted) const;
    AutomationStepEventComponent *getNextEventComponent(int indexOfSorted) const;

    Rectangle<float> getEventBounds(AutomationStepEventComponent *c) const;
    Rectangle<float> getEventBounds(float targetBeat, float sequenceLength,
        bool isPedalDown, float anchor) const;

    friend class AutomationStepEventComponent;
    friend class AutomationStepEventsConnector;

private:

    void updateEventComponent(AutomationStepEventComponent *component) const;
    void reloadTrack();

    HybridRoll &roll;
    ProjectTreeItem &project;
    WeakReference<MidiSequence> sequence;

    ScopedPointer<AutomationStepEventsConnector> leadingConnector;

    OwnedArray<AutomationStepEventComponent> eventComponents;
    SparseHashMap<AutomationEvent, AutomationStepEventComponent *, MidiEventHash> eventsHash;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutomationStepsClipComponent)
};
