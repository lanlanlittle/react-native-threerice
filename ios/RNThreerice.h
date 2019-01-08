
#if __has_include("RCTBridgeModule.h")
#import "RCTBridgeModule.h"
#else
#import <React/RCTBridgeModule.h>
#endif

@interface RNThreerice : NSObject <RCTBridgeModule>
@property NSString* rice_appId;
@property NSString* rice_appSecret;

- (NSString*)getValueByKey:(NSString*) key;

@end
  
