/*
 * Copyright (c) 2016 Igalia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ScrollAnimatorGtk_h
#define ScrollAnimatorGtk_h

#include "ScrollAnimator.h"
#include "Timer.h"

namespace WebCore {

class ScrollAnimation;

class ScrollAnimatorGtk final : public ScrollAnimator {
public:
    explicit ScrollAnimatorGtk(ScrollableArea&);
    virtual ~ScrollAnimatorGtk();

private:
#if ENABLE(SMOOTH_SCROLLING)
    bool scroll(ScrollbarOrientation, ScrollGranularity, float step, float multiplier) override;
    void scrollToOffsetWithoutAnimation(const FloatPoint&) override;
    void willEndLiveResize() override;
#endif

    void didAddVerticalScrollbar(Scrollbar*) override;
    void didAddHorizontalScrollbar(Scrollbar*) override;
    void willRemoveVerticalScrollbar(Scrollbar*) override;
    void willRemoveHorizontalScrollbar(Scrollbar*) override;

    void mouseEnteredContentArea() override;
    void mouseExitedContentArea() override;
    void mouseMovedInContentArea() override;
    void contentAreaDidShow() override;
    void contentAreaDidHide() override;
    void notifyContentAreaScrolled(const FloatSize& delta) override;
    void lockOverlayScrollbarStateToHidden(bool) override;

    void overlayScrollbarAnimationTimerFired();
    void showOverlayScrollbars();
    void hideOverlayScrollbars();
    void updateOverlayScrollbarsOpacity();

#if ENABLE(SMOOTH_SCROLLING)
    void ensureSmoothScrollingAnimation();

    std::unique_ptr<ScrollAnimation> m_animation;
#endif
    Scrollbar* m_horizontalOverlayScrollbar { nullptr };
    Scrollbar* m_verticalOverlayScrollbar { nullptr };
    bool m_overlayScrollbarsLocked { false };
    Timer m_overlayScrollbarAnimationTimer;
    double m_overlayScrollbarAnimationSource { 0 };
    double m_overlayScrollbarAnimationTarget { 0 };
    double m_overlayScrollbarAnimationCurrent { 0 };
    MonotonicTime m_overlayScrollbarAnimationStartTime;
    MonotonicTime m_overlayScrollbarAnimationEndTime;
};

} // namespace WebCore

#endif // ScrollAnimatorGtk_h
