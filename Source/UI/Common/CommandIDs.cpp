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
#include "CommandIDs.h"

#define CASE_FOR(x) \
    case constexprHash(#x): \
    return x; \

CommandIDs::Id CommandIDs::getIdForName(const String &command)
{
    switch (constexprHash(command.toRawUTF8()))
    {
        CASE_FOR(Back)
        CASE_FOR(Cancel)
        CASE_FOR(Browse)
        CASE_FOR(IconButtonPressed)
        CASE_FOR(HideDialog)
        CASE_FOR(HideCallout)
        CASE_FOR(DismissModalDialogAsync)
        CASE_FOR(AddAnnotation)
        CASE_FOR(AddTimeSignature)
        CASE_FOR(AddKeySignature)
        CASE_FOR(JumpToAnnotation)
        CASE_FOR(CreateArpeggiatorFromSelection)
        CASE_FOR(InitWorkspace)
        CASE_FOR(ScanAllPlugins)
        CASE_FOR(ScanPluginsFolder)
        CASE_FOR(DeleteTrack)
        CASE_FOR(RenameTrack)
        CASE_FOR(SelectAllEvents)
        CASE_FOR(SelectAllClips)
        CASE_FOR(NewTrackFromSelection)
        CASE_FOR(DuplicateTrack)
        CASE_FOR(EditCurrentInstrument)
        CASE_FOR(SwitchToClipInViewport)
        CASE_FOR(Tuplet1)
        CASE_FOR(Tuplet2)
        CASE_FOR(Tuplet3)
        CASE_FOR(Tuplet4)
        CASE_FOR(Tuplet5)
        CASE_FOR(Tuplet6)
        CASE_FOR(Tuplet7)
        CASE_FOR(Tuplet8)
        CASE_FOR(Tuplet9)
        CASE_FOR(QuantizeTo1_1)
        CASE_FOR(QuantizeTo1_2)
        CASE_FOR(QuantizeTo1_4)
        CASE_FOR(QuantizeTo1_8)
        CASE_FOR(QuantizeTo1_16)
        CASE_FOR(QuantizeTo1_32)
        CASE_FOR(DeleteEvents)
        CASE_FOR(CopyEvents)
        CASE_FOR(CutEvents)
        CASE_FOR(PasteEvents)
        CASE_FOR(DeleteClips)
        CASE_FOR(CopyClips)
        CASE_FOR(CutClips)
        CASE_FOR(PasteClips)
        CASE_FOR(ClipTransposeUp)
        CASE_FOR(ClipTransposeDown)
        CASE_FOR(ClipTransposeOctaveUp)
        CASE_FOR(ClipTransposeOctaveDown)
        CASE_FOR(ClipVolumeUp)
        CASE_FOR(ClipVolumeDown)
        CASE_FOR(ToggleMuteClips)
        CASE_FOR(ToggleSoloClips)
        CASE_FOR(ToggleScalesHighlighting)
        CASE_FOR(ToggleNoteNameGuides)
        CASE_FOR(ToggleLoopOverSelection)
        CASE_FOR(ZoomIn)
        CASE_FOR(ZoomOut)
        CASE_FOR(ZoomEntireClip)
        CASE_FOR(Undo)
        CASE_FOR(Redo)
        CASE_FOR(TimelineJumpNext)
        CASE_FOR(TimelineJumpPrevious)
        CASE_FOR(TimelineJumpHome)
        CASE_FOR(TimelineJumpEnd)
        CASE_FOR(ResetPreviewChanges)
        CASE_FOR(TransportRecordingAwait)
        CASE_FOR(TransportRecordingStart)
        CASE_FOR(TransportPlaybackStart)
        CASE_FOR(TransportStop)
        CASE_FOR(PopupMenuDismiss)
        CASE_FOR(RenderToFLAC)
        CASE_FOR(RenderToWAV)
        CASE_FOR(ImportMidi)
        CASE_FOR(ExportMidi)
        CASE_FOR(DeleteProject)
        CASE_FOR(ProjectTransposeUp)
        CASE_FOR(ProjectTransposeDown)
        CASE_FOR(ProjectSetOneTempo)
        CASE_FOR(SelectFunction)
        CASE_FOR(SelectScale)
        CASE_FOR(SelectTimeSignature)
        CASE_FOR(SelectVersion)
        CASE_FOR(SwitchBetweenRolls)
        CASE_FOR(SwitchToEditMode)
        CASE_FOR(SwitchToArrangeMode)
        CASE_FOR(SwitchToVersioningMode)
        CASE_FOR(ShowPreviousPage)
        CASE_FOR(ShowNextPage)
        CASE_FOR(ShowRootPage)
        CASE_FOR(ToggleShowHideCombo)
        CASE_FOR(StartDragViewport)
        CASE_FOR(EndDragViewport)
        CASE_FOR(SelectAudioDeviceType)
        CASE_FOR(SelectAudioDevice)
        CASE_FOR(SelectSampleRate)
        CASE_FOR(SelectBufferSize)
        CASE_FOR(SelectMidiInputDevice)
        CASE_FOR(SelectFont)
        CASE_FOR(EditModeDefault)
        CASE_FOR(EditModeDraw)
        CASE_FOR(EditModePan)
        CASE_FOR(EditModeSelect)
        CASE_FOR(EditModeKnife)
        CASE_FOR(EditModeEraser)
        CASE_FOR(EditModeChordBuilder)
        CASE_FOR(BeatShiftLeft)
        CASE_FOR(BeatShiftRight)
        CASE_FOR(LengthIncrease)
        CASE_FOR(LengthDecrease)
        CASE_FOR(KeyShiftUp)
        CASE_FOR(KeyShiftDown)
        CASE_FOR(OctaveShiftUp)
        CASE_FOR(OctaveShiftDown)
        CASE_FOR(CleanupOverlaps)
        CASE_FOR(InvertChordUp)
        CASE_FOR(InvertChordDown)
        CASE_FOR(MelodicInversion)
        CASE_FOR(Retrograde)
        CASE_FOR(ShowArpeggiatorsPanel)
        CASE_FOR(ShowVolumePanel)
        CASE_FOR(ShowRescalePanel)
        CASE_FOR(ShowScalePanel)
        CASE_FOR(ShowChordPanel)
        CASE_FOR(ShowNewTrackPanel)
        CASE_FOR(NotesVolumeRandom)
        CASE_FOR(NotesVolumeFadeOut)
        CASE_FOR(NotesVolumeUp)
        CASE_FOR(NotesVolumeDown)
        CASE_FOR(VersionControlToggleQuickStash)
        CASE_FOR(VersionControlPushSelected)
        CASE_FOR(VersionControlPullSelected)
        CASE_FOR(VersionControlSyncAll)
        CASE_FOR(VersionControlResetAll)
        CASE_FOR(VersionControlCommitAll)
        CASE_FOR(VersionControlSelectAll)
        CASE_FOR(VersionControlSelectNone)
        CASE_FOR(VersionControlResetSelected)
        CASE_FOR(VersionControlCommitSelected)
        CASE_FOR(VersionControlCheckout)
        CASE_FOR(PatternsGroupByName)
        CASE_FOR(PatternsGroupByColour)
        CASE_FOR(PatternsGroupByInstrument)
        CASE_FOR(PatternsGroupById)
        CASE_FOR(CommandPalette)
        CASE_FOR(CommandPaletteWithMode)
        CASE_FOR(KeyMapReset)
        CASE_FOR(KeyMapLoadScala)
        CASE_FOR(KeyMapNextPage)
        CASE_FOR(KeyMapPreviousPage)
        CASE_FOR(KeyMapCopyToClipboard)
        CASE_FOR(KeyMapPasteFromClipboard)
        default: return None;
    }
}

#define TRANS_KEY(x, y) \
    case x: \
    return y; \

#define TRANS_NONE(x) \
    case x: \
    return 0; \

// this is only used for command palette:
// only the commands with translations are displayed
I18n::Key CommandIDs::getTranslationKeyFor(CommandIDs::Id id)
{
    using namespace I18n;

    switch (id)
    {
        TRANS_NONE(Back)
        TRANS_NONE(Cancel)
        TRANS_NONE(Browse)
        TRANS_NONE(IconButtonPressed)
        TRANS_NONE(HideDialog)
        TRANS_NONE(HideCallout)
        TRANS_NONE(DismissModalDialogAsync)
        TRANS_KEY(AddAnnotation, Menu::annotationAdd)
        TRANS_KEY(AddTimeSignature, Menu::timeSignatureAdd)
        TRANS_KEY(AddKeySignature, Menu::keySignatureAdd)
        TRANS_NONE(JumpToAnnotation)
        TRANS_NONE(CreateArpeggiatorFromSelection)
        //TRANS_KEY(CreateArpeggiatorFromSelection, Menu::arpeggiatorsCreate)
        TRANS_NONE(InitWorkspace)
        TRANS_KEY(ScanAllPlugins, Menu::instrumentsReload)
        TRANS_KEY(ScanPluginsFolder, Menu::instrumentsScanFolder)
        TRANS_KEY(DeleteTrack, Menu::trackDelete)
        TRANS_KEY(RenameTrack, Menu::trackRename)
        TRANS_KEY(SelectAllEvents, Menu::trackSelectall)
        TRANS_NONE(SelectAllClips)
        TRANS_KEY(NewTrackFromSelection, Menu::Selection::notesToTrack)
        TRANS_KEY(DuplicateTrack, Menu::trackDuplicate)
        TRANS_KEY(EditCurrentInstrument, Menu::instrumentShowWindow)
        TRANS_NONE(SwitchToClipInViewport)
        TRANS_KEY(Tuplet1, Menu::tuplet1)
        TRANS_KEY(Tuplet2, Menu::tuplet2)
        TRANS_KEY(Tuplet3, Menu::tuplet3)
        TRANS_KEY(Tuplet4, Menu::tuplet4)
        TRANS_KEY(Tuplet5, Menu::tuplet5)
        TRANS_KEY(Tuplet6, Menu::tuplet6)
        TRANS_KEY(Tuplet7, Menu::tuplet7)
        TRANS_KEY(Tuplet8, Menu::tuplet8)
        TRANS_KEY(Tuplet9, Menu::tuplet9)
        TRANS_KEY(QuantizeTo1_1, Menu::quantizeTo1_1)
        TRANS_KEY(QuantizeTo1_2, Menu::quantizeTo1_2)
        TRANS_KEY(QuantizeTo1_4, Menu::quantizeTo1_4)
        TRANS_KEY(QuantizeTo1_8, Menu::quantizeTo1_8)
        TRANS_KEY(QuantizeTo1_16, Menu::quantizeTo1_16)
        TRANS_KEY(QuantizeTo1_32, Menu::quantizeTo1_32)
        TRANS_KEY(DeleteEvents, Menu::delete_)
        TRANS_KEY(CopyEvents, Menu::copy)
        TRANS_KEY(CutEvents, Menu::cut)
        TRANS_KEY(PasteEvents, Menu::paste)
        TRANS_KEY(DeleteClips, Menu::delete_)
        TRANS_KEY(CopyClips, Menu::copy)
        TRANS_KEY(CutClips, Menu::cut)
        TRANS_KEY(PasteClips, Menu::paste)
        TRANS_KEY(ClipTransposeUp, Menu::Selection::clipsTransposeUp)
        TRANS_KEY(ClipTransposeDown, Menu::Selection::clipsTransposeDown)
        TRANS_NONE(ClipTransposeOctaveUp)
        TRANS_NONE(ClipTransposeOctaveDown)
        TRANS_NONE(ClipVolumeUp)
        TRANS_NONE(ClipVolumeDown)
        TRANS_KEY(ToggleMuteClips, CommandPalette::toggleMute)
        TRANS_KEY(ToggleSoloClips, CommandPalette::toggleSolo)
        TRANS_KEY(ToggleScalesHighlighting, CommandPalette::toggleScalesHighlighting)
        TRANS_KEY(ToggleNoteNameGuides, CommandPalette::toggleNoteNameGuides)
        TRANS_KEY(ToggleLoopOverSelection, CommandPalette::toggleLoopOverSelection)
        TRANS_NONE(ZoomIn)
        TRANS_NONE(ZoomOut)
        TRANS_KEY(ZoomEntireClip, Menu::Selection::clipsEdit)
        TRANS_NONE(Undo)
        TRANS_NONE(Redo)
        TRANS_NONE(TimelineJumpNext)
        TRANS_NONE(TimelineJumpPrevious)
        TRANS_NONE(TimelineJumpHome)
        TRANS_NONE(TimelineJumpEnd)
        TRANS_NONE(ResetPreviewChanges)
        TRANS_NONE(TransportRecordingAwait) // todo translations for recording cmds?
        TRANS_NONE(TransportRecordingStart)
        TRANS_NONE(TransportPlaybackStart)
        TRANS_NONE(TransportStop)
        TRANS_NONE(PopupMenuDismiss)
        TRANS_KEY(RenderToFLAC, Menu::Project::renderFlac)
        TRANS_KEY(RenderToWAV, Menu::Project::renderWav)
        TRANS_KEY(ImportMidi, Menu::Project::importMidi)
        TRANS_KEY(ExportMidi, Menu::Project::renderMidi)
        TRANS_KEY(DeleteProject, Menu::Project::deleteConfirm)
        TRANS_KEY(ProjectTransposeUp, Menu::Project::transposeUp)
        TRANS_KEY(ProjectTransposeDown, Menu::Project::transposeDown)
        TRANS_KEY(ProjectSetOneTempo, Menu::setOneTempo)
        TRANS_NONE(SelectFunction)
        TRANS_NONE(SelectScale)
        TRANS_NONE(SelectTimeSignature)
        TRANS_NONE(SelectVersion)
        TRANS_NONE(SwitchBetweenRolls)
        TRANS_KEY(SwitchToEditMode, Menu::Project::editorLinear)
        TRANS_KEY(SwitchToArrangeMode, Menu::Project::editorPattern)
        TRANS_KEY(SwitchToVersioningMode, Menu::Project::editorVcs)
        TRANS_NONE(ShowPreviousPage)
        TRANS_NONE(ShowNextPage)
        TRANS_NONE(ShowRootPage)
        TRANS_NONE(ToggleShowHideCombo)
        TRANS_NONE(StartDragViewport)
        TRANS_NONE(EndDragViewport)
        TRANS_NONE(SelectAudioDeviceType)
        TRANS_NONE(SelectAudioDevice)
        TRANS_NONE(SelectSampleRate)
        TRANS_NONE(SelectBufferSize)
        TRANS_NONE(SelectMidiInputDevice)
        TRANS_NONE(SelectFont)
        TRANS_NONE(EditModeDefault)
        TRANS_NONE(EditModeDraw)
        TRANS_NONE(EditModePan)
        TRANS_NONE(EditModeSelect)
        TRANS_NONE(EditModeKnife)
        TRANS_NONE(EditModeEraser)
        TRANS_NONE(EditModeChordBuilder)
        TRANS_NONE(BeatShiftLeft)
        TRANS_NONE(BeatShiftRight)
        TRANS_NONE(LengthIncrease)
        TRANS_NONE(LengthDecrease)
        TRANS_NONE(KeyShiftUp)
        TRANS_NONE(KeyShiftDown)
        TRANS_NONE(OctaveShiftUp)
        TRANS_NONE(OctaveShiftDown)
        TRANS_KEY(CleanupOverlaps, Menu::refactoringCleanup)
        TRANS_KEY(InvertChordUp, Menu::refactoringInverseUp)
        TRANS_KEY(InvertChordDown, Menu::refactoringInverseDown)
        TRANS_KEY(MelodicInversion, Menu::refactoringMelodicInversion)
        TRANS_KEY(Retrograde, Menu::refactoringRetrograde)
        TRANS_NONE(ShowArpeggiatorsPanel)
        TRANS_NONE(ShowVolumePanel)
        TRANS_NONE(ShowRescalePanel)
        TRANS_NONE(ShowScalePanel)
        TRANS_NONE(ShowChordPanel)
        TRANS_NONE(ShowNewTrackPanel)
        TRANS_NONE(NotesVolumeRandom)
        TRANS_NONE(NotesVolumeFadeOut)
        TRANS_NONE(NotesVolumeUp)
        TRANS_NONE(NotesVolumeDown)
        TRANS_KEY(VersionControlToggleQuickStash, Menu::vcsChangesToggle)
        TRANS_KEY(VersionControlPushSelected, Menu::Selection::vcsPush)
        TRANS_KEY(VersionControlPullSelected, Menu::Selection::vcsPull)
        TRANS_KEY(VersionControlSyncAll, Menu::vcsSyncAll)
        TRANS_KEY(VersionControlResetAll, Menu::vcsResetAll)
        TRANS_KEY(VersionControlCommitAll, Menu::vcsCommitAll)
        TRANS_KEY(VersionControlSelectAll, Menu::Selection::vcsSelectAll)
        TRANS_KEY(VersionControlSelectNone, Menu::Selection::vcsSelectNone)
        TRANS_KEY(VersionControlResetSelected, Menu::Selection::vcsReset)
        TRANS_KEY(VersionControlCommitSelected, Menu::Selection::vcsCommit)
        TRANS_KEY(VersionControlCheckout, Menu::Selection::vcsCheckout)
        TRANS_KEY(PatternsGroupByName, Menu::groupByName)
        TRANS_KEY(PatternsGroupByColour, Menu::groupByColour)
        TRANS_KEY(PatternsGroupByInstrument, Menu::groupByInstrument)
        TRANS_KEY(PatternsGroupById, Menu::groupByNone)
        TRANS_NONE(CommandPalette)
        TRANS_NONE(CommandPaletteWithMode)
        TRANS_KEY(KeyMapReset, Menu::keyboardMappingLoadScala)
        TRANS_KEY(KeyMapLoadScala, Menu::keyboardMappingReset)
        TRANS_NONE(KeyMapNextPage)
        TRANS_NONE(KeyMapPreviousPage)
        TRANS_KEY(KeyMapCopyToClipboard, Menu::copy)
        TRANS_KEY(KeyMapPasteFromClipboard, Menu::paste)
        default: return {};
    }
}
