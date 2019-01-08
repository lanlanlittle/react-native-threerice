//
//  UMWSDK.h
//  UMWinSDK
//
//  Created by wangwei on 15-8-12.
//  Copyright (c) 2015年 UMWin Mobile Co. Ltd. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "publicconfuse.h"


@interface UMWSDK : NSObject

#pragma mark - 基础设置
// !!!: 应用ID
/*
 设置appid和appSecret（在有米后台创建应用时生成的id与key）
 */
+ (void)UMWLaunchWithAppID:(NSString *)UMWAppid UMWAppSecret:(NSString *)UMWAppSecret;


// !!!:设置广告显示需要的window [当积分墙不能正常显示出来的时候设置]
/*
 *可以在[AppDelegate application:didFinishLaunchingWithOptions:]里[self.window makeKeyAndVisible];后设置[UMWSDK  UMWSetApplicationWindow:self.window];
 */
+ (void)UMWSetApplicationWindow:(UIWindow *)window;

// !!!:设置UserID
/*
 *用于积分回调，你设置什么。回调的时候，userID字段就返回什么
 */
+ (void)UMWSetUserID:(NSString *)UMWUserID;
+ (NSString *)UMWUserID;


#pragma mark - 展示有米积分墙
//!!!: 显示积分墙
/* 
 *param didShowBlockIn: 成功显示积分墙后的回调block
 *param didDismissBlockIn: 关闭积分墙后的回调block
 *returns 是否显示积分墙成功，积分墙显示不成功并不会调用didShowBlockIn和didDismissBlockIn
 */
+ (UIViewController *)UMWGetViewController:(void (^)(void))UMWDidShowBlock UMWinDidDismissBlock:(void (^)(UIViewController *viewController))UMWinDidDismissBlockIn;

/*
 *关闭积分墙
 */
+ (void)UMWClose;


#pragma mark - 积分查询
//当有任务被完成了。调用这个积分查询接口，刚刚完成的任务获得的积分信息就再pointInfo
+ (void)UMWCheckPointsWithCallbackBlock:(void(^)(NSArray *PointInfo))callback;

@end
