
#import "RNThreerice.h"
#import "UMWSDK.h"

@implementation RNThreerice

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.rice_appId = [self getValueByKey:@"rice_appId"];
        self.rice_appSecret = [self getValueByKey:@"rice_appSecret"];
        [UMWSDK UMWLaunchWithAppID:self.rice_appId UMWAppSecret:self.rice_appSecret];
    }
    return self;
}

- (NSString*)getValueByKey:(NSString*) key{
    NSDictionary* dictBundle = [[NSBundle mainBundle ] infoDictionary];
    if (dictBundle)
    {
        NSString* value = [dictBundle objectForKey:key];
        if(value == NULL) return @"";
        return value;
    }
    
    return @"";
}

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(openThreeRice:(NSDictionary*)dict)
{
    if(dict == NULL) return;
    NSString* userid = [dict objectForKey:@"userid"];
    if(userid != NULL){
        [UMWSDK UMWSetUserID:userid];
    }
    
    UIViewController *viewController = [UMWSDK UMWGetViewController:^{
        NSLog(@"积分墙打开");
    } UMWinDidDismissBlock:^(UIViewController *viewController){
        NSLog(@"积分墙关闭");
        [viewController dismissViewControllerAnimated:YES completion:nil];
    }];
    UIWindow* parent = [UIApplication sharedApplication].keyWindow;
    if(parent != NULL){
        [parent.rootViewController presentViewController:viewController animated:YES completion:nil];
    }
}

@end
  
