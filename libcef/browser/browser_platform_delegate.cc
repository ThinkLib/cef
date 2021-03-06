// Copyright 2015 The Chromium Embedded Framework Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/browser/browser_platform_delegate.h"

#include "libcef/browser/browser_host_impl.h"
#include "libcef/browser/osr/browser_platform_delegate_osr.h"
#include "libcef/browser/web_contents_dialog_helper.h"
#include "libcef/common/extensions/extensions_util.h"

#include "base/logging.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/render_widget_host.h"

CefBrowserPlatformDelegate::CefBrowserPlatformDelegate() {}

CefBrowserPlatformDelegate::~CefBrowserPlatformDelegate() {
  DCHECK(!browser_);
}

void CefBrowserPlatformDelegate::CreateViewForWebContents(
    content::WebContentsView** view,
    content::RenderViewHostDelegateView** delegate_view) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::WebContentsCreated(
    content::WebContents* web_contents) {}

void CefBrowserPlatformDelegate::RenderViewCreated(
    content::RenderViewHost* render_view_host) {
  // Indicate that the view has an external parent (namely us). This changes the
  // default view behavior in some cases (e.g. focus handling on Linux).
  if (!IsViewsHosted() && render_view_host->GetWidget()->GetView())
    render_view_host->GetWidget()->GetView()->SetHasExternalParent(true);
}

void CefBrowserPlatformDelegate::BrowserCreated(CefBrowserHostImpl* browser) {
  DCHECK(!browser_);
  DCHECK(browser);
  browser_ = browser;

  if (browser_->IsPrintPreviewSupported()) {
    web_contents_dialog_helper_.reset(
        new CefWebContentsDialogHelper(browser_->web_contents(), this));
  }
}

void CefBrowserPlatformDelegate::NotifyBrowserCreated() {}

void CefBrowserPlatformDelegate::NotifyBrowserDestroyed() {}

void CefBrowserPlatformDelegate::BrowserDestroyed(CefBrowserHostImpl* browser) {
  DCHECK(browser_ && browser_ == browser);
  browser_ = nullptr;
}

bool CefBrowserPlatformDelegate::CreateHostWindow() {
  NOTREACHED();
  return true;
}

void CefBrowserPlatformDelegate::CloseHostWindow() {
  NOTREACHED();
}

#if defined(USE_AURA)
views::Widget* CefBrowserPlatformDelegate::GetWindowWidget() const {
  NOTREACHED();
  return nullptr;
}

CefRefPtr<CefBrowserView> CefBrowserPlatformDelegate::GetBrowserView() const {
  NOTREACHED();
  return nullptr;
}
#endif

void CefBrowserPlatformDelegate::PopupWebContentsCreated(
    const CefBrowserSettings& settings,
    CefRefPtr<CefClient> client,
    content::WebContents* new_web_contents,
    CefBrowserPlatformDelegate* new_platform_delegate,
    bool is_devtools) {}

void CefBrowserPlatformDelegate::PopupBrowserCreated(
    CefBrowserHostImpl* new_browser,
    bool is_devtools) {}

void CefBrowserPlatformDelegate::SendCaptureLostEvent() {
  content::RenderWidgetHostImpl* widget = content::RenderWidgetHostImpl::From(
      browser_->web_contents()->GetRenderViewHost()->GetWidget());
  if (widget)
    widget->LostCapture();
}

#if defined(OS_WIN) || (defined(OS_POSIX) && !defined(OS_MACOSX))
void CefBrowserPlatformDelegate::NotifyMoveOrResizeStarted() {
  // Dismiss any existing popups.
  content::RenderViewHost* host = browser_->web_contents()->GetRenderViewHost();
  if (host)
    host->NotifyMoveOrResizeStarted();
}

void CefBrowserPlatformDelegate::SizeTo(int width, int height) {}
#endif

std::unique_ptr<CefFileDialogRunner>
CefBrowserPlatformDelegate::CreateFileDialogRunner() {
  return nullptr;
}

std::unique_ptr<CefJavaScriptDialogRunner>
CefBrowserPlatformDelegate::CreateJavaScriptDialogRunner() {
  return nullptr;
}

void CefBrowserPlatformDelegate::WasHidden(bool hidden) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::NotifyScreenInfoChanged() {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::Invalidate(cef_paint_element_type_t type) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::SendExternalBeginFrame() {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::SetWindowlessFrameRate(int frame_rate) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::ImeSetComposition(
    const CefString& text,
    const std::vector<CefCompositionUnderline>& underlines,
    const CefRange& replacement_range,
    const CefRange& selection_range) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::ImeCommitText(
    const CefString& text,
    const CefRange& replacement_range,
    int relative_cursor_pos) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::ImeFinishComposingText(bool keep_selection) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::ImeCancelComposition() {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::DragTargetDragEnter(
    CefRefPtr<CefDragData> drag_data,
    const CefMouseEvent& event,
    cef_drag_operations_mask_t allowed_ops) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::DragTargetDragOver(
    const CefMouseEvent& event,
    cef_drag_operations_mask_t allowed_ops) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::DragTargetDragLeave() {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::DragTargetDrop(const CefMouseEvent& event) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::StartDragging(
    const content::DropData& drop_data,
    blink::WebDragOperationsMask allowed_ops,
    const gfx::ImageSkia& image,
    const gfx::Vector2d& image_offset,
    const content::DragEventSourceInfo& event_info,
    content::RenderWidgetHostImpl* source_rwh) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::UpdateDragCursor(
    blink::WebDragOperation operation) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::DragSourceEndedAt(
    int x,
    int y,
    cef_drag_operations_mask_t op) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::DragSourceSystemDragEnded() {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::AccessibilityEventReceived(
    const content::AXEventNotificationDetails& eventData) {
  NOTREACHED();
}

void CefBrowserPlatformDelegate::AccessibilityLocationChangesReceived(
    const std::vector<content::AXLocationChangeNotificationDetails>& locData) {
  NOTREACHED();
}

gfx::Point CefBrowserPlatformDelegate::GetDialogPosition(
    const gfx::Size& size) {
  NOTREACHED();
  return gfx::Point();
}

gfx::Size CefBrowserPlatformDelegate::GetMaximumDialogSize() {
  NOTREACHED();
  return gfx::Size();
}

base::RepeatingClosure CefBrowserPlatformDelegate::GetBoundsChangedCallback() {
  if (web_contents_dialog_helper_) {
    return web_contents_dialog_helper_->GetBoundsChangedCallback();
  }

  return base::RepeatingClosure();
}

// static
int CefBrowserPlatformDelegate::TranslateWebEventModifiers(
    uint32 cef_modifiers) {
  int result = 0;
  // Set modifiers based on key state.
  if (cef_modifiers & EVENTFLAG_SHIFT_DOWN)
    result |= blink::WebInputEvent::kShiftKey;
  if (cef_modifiers & EVENTFLAG_CONTROL_DOWN)
    result |= blink::WebInputEvent::kControlKey;
  if (cef_modifiers & EVENTFLAG_ALT_DOWN)
    result |= blink::WebInputEvent::kAltKey;
  if (cef_modifiers & EVENTFLAG_COMMAND_DOWN)
    result |= blink::WebInputEvent::kMetaKey;
  if (cef_modifiers & EVENTFLAG_LEFT_MOUSE_BUTTON)
    result |= blink::WebInputEvent::kLeftButtonDown;
  if (cef_modifiers & EVENTFLAG_MIDDLE_MOUSE_BUTTON)
    result |= blink::WebInputEvent::kMiddleButtonDown;
  if (cef_modifiers & EVENTFLAG_RIGHT_MOUSE_BUTTON)
    result |= blink::WebInputEvent::kRightButtonDown;
  if (cef_modifiers & EVENTFLAG_CAPS_LOCK_ON)
    result |= blink::WebInputEvent::kCapsLockOn;
  if (cef_modifiers & EVENTFLAG_NUM_LOCK_ON)
    result |= blink::WebInputEvent::kNumLockOn;
  if (cef_modifiers & EVENTFLAG_IS_LEFT)
    result |= blink::WebInputEvent::kIsLeft;
  if (cef_modifiers & EVENTFLAG_IS_RIGHT)
    result |= blink::WebInputEvent::kIsRight;
  if (cef_modifiers & EVENTFLAG_IS_KEY_PAD)
    result |= blink::WebInputEvent::kIsKeyPad;
  return result;
}
