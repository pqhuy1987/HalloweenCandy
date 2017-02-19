#import <UIKit/UIKit.h>
#import "GADBannerView.h"
#import "GADBannerViewDelegate.h"

@class RootViewController;
@class GADBannerView;
@class GADBannerViewDelegate;

@interface AppController : NSObject <UIApplicationDelegate, GADBannerViewDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView *bannerAd; //新增代码
}
@end