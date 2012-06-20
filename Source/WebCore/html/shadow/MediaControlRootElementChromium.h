/*
 * Copyright (C) 2007, 2008, 2009, 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MediaControlRootElementChromium_h
#define MediaControlRootElementChromium_h

#if ENABLE(VIDEO)

#include "MediaControls.h"
#include <wtf/RefPtr.h>

namespace WebCore {

class Document;
class HTMLInputElement;
class Event;
class MediaControlPanelMuteButtonElement;
class MediaControlPlayButtonElement;
class MediaControlCurrentTimeDisplayElement;
class MediaControlTimeRemainingDisplayElement;
class MediaControlTimelineElement;
class MediaControlVolumeSliderElement;
class MediaControlFullscreenButtonElement;
class MediaControlTimeDisplayElement;
class MediaControlTimelineContainerElement;
class MediaControlMuteButtonElement;
class MediaControlVolumeSliderElement;
class MediaControlPanelElement;
class MediaControlChromiumEnclosureElement;
class MediaControllerInterface;
class MediaPlayer;

class RenderBox;
class RenderMedia;

#if ENABLE(VIDEO_TRACK)
class MediaControlTextTrackContainerElement;
class MediaControlTextTrackDisplayElement;
#endif

class MediaControlChromiumEnclosureElement : public HTMLDivElement {
public:
    static PassRefPtr<MediaControlChromiumEnclosureElement> create(Document*);

    virtual const AtomicString& shadowPseudoId() const;

    void setMediaController(MediaControllerInterface* controller) { m_mediaController = controller; }
    MediaControllerInterface* mediaController() const { return m_mediaController; }

protected:
    MediaControlChromiumEnclosureElement(Document*);

private:
    virtual bool isMediaControlElement() const { return true; }

    MediaControllerInterface* m_mediaController;
};

class MediaControlRootElementChromium : public MediaControls {
public:
    static PassRefPtr<MediaControlRootElementChromium> create(Document*);

    // MediaControls implementation.
    void setMediaController(MediaControllerInterface*);

    void show();
    void hide();
    void makeOpaque();
    void makeTransparent();

    void reset();

    void playbackProgressed();
    void playbackStarted();
    void playbackStopped();

    void changedMute();
    void changedVolume();

    void enteredFullscreen();
    void exitedFullscreen();

    void reportedError();
    void loadedMetadata();
    void changedClosedCaptionsVisibility();

    void showVolumeSlider();
    void updateTimeDisplay();
    void updateStatusDisplay();

#if ENABLE(VIDEO_TRACK)
    void createTextTrackDisplay();
    void showTextTrackDisplay();
    void hideTextTrackDisplay();
    void updateTextTrackDisplay();
#endif

    void bufferingProgressed();

    virtual bool shouldHideControls();

private:
    MediaControlRootElementChromium(Document*);

    virtual void defaultEventHandler(Event*);
    void hideFullscreenControlsTimerFired(Timer<MediaControlRootElementChromium>*);
    void startHideFullscreenControlsTimer();
    void stopHideFullscreenControlsTimer();

    virtual const AtomicString& shadowPseudoId() const;

    bool containsRelatedTarget(Event*);

    MediaControllerInterface* m_mediaController;

    MediaControlPlayButtonElement* m_playButton;
    MediaControlCurrentTimeDisplayElement* m_currentTimeDisplay;
    MediaControlTimeRemainingDisplayElement* m_durationDisplay;
    MediaControlTimelineElement* m_timeline;
    MediaControlTimelineContainerElement* m_timelineContainer;
    MediaControlPanelMuteButtonElement* m_panelMuteButton;
    MediaControlVolumeSliderElement* m_volumeSlider;
#if ENABLE(FULLSCREEN_MEDIA_CONTROLS)
    MediaControlFullscreenButtonElement* m_fullscreenButton;
#endif
    MediaControlPanelElement* m_panel;
    MediaControlChromiumEnclosureElement* m_enclosure;
#if ENABLE(VIDEO_TRACK)
    MediaControlTextTrackContainerElement* m_textDisplayContainer;
#endif

    bool m_opaque;
    Timer<MediaControlRootElementChromium> m_hideFullscreenControlsTimer;
    bool m_isMouseOverControls;
    bool m_isFullscreen;
};

}

#endif

#endif
