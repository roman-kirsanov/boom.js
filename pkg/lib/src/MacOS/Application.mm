#include <iostream>
#include <Cocoa/Cocoa.h>
#include <Boom/Application.hpp>

@interface __Delegate : NSObject<NSApplicationDelegate>

- (id)initWithOnRun:(void(^)(void))onRun onExit:(void(^)(void))onExit;

@end

@implementation __Delegate {
    void (^_onRun)(void);
    void (^_onExit)(void);
}

- (id)initWithOnRun:(void(^)(void))onRun onExit:(void(^)(void))onExit {
    self = [super init];
    if (self) {
        _onRun = onRun;
        _onExit = onExit;
    }
    return self;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
    _onRun();
}

- (void)exit {
    _onExit();
}

@end

namespace boom {

void App::_implInit() {
    [[NSApplication sharedApplication]
        setDelegate: [[__Delegate alloc]
            initWithOnRun: ^{
                id mainMenu = [[NSMenu alloc] init];
                id appMenu = [[NSMenu alloc] init];
                id appItem = [mainMenu addItemWithTitle: [NSString stringWithCString: "123" encoding: NSUTF8StringEncoding] action: nil keyEquivalent: @""];
                id quitItem = [appMenu addItemWithTitle: @"Quit" action: nil keyEquivalent: @"q"];
                [quitItem setTarget: [NSApp delegate]];
                [quitItem setAction: @selector(exit)];
                [appItem setSubmenu: appMenu];
                [NSApp setMainMenu: mainMenu];
                [NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];
                [NSApp activateIgnoringOtherApps: YES];
            }
            onExit: ^{
                _onExit();
                onExit.emit();
            }
        ]
    ];
    [NSApp finishLaunching];
}

void App::_implDone() {
    [[NSApplication sharedApplication] setDelegate: nil];
}

void App::_implSetTitle(std::string const& title) {

}

void App::_implPollEvents(double timeout) {
    NSEvent* event = [NSApp nextEventMatchingMask: NSEventMaskAny
                                        untilDate: ((timeout > 0) ? [NSDate dateWithTimeIntervalSinceNow: (timeout / 1000.0)] : nil)
                                           inMode: NSDefaultRunLoopMode
                                          dequeue: YES];
    if (event != nil) {
        [NSApp sendEvent: event];
        [NSApp updateWindows];
    }
}

} /* namespace boom */
