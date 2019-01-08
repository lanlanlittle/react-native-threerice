//
//  uMWinFeaturedAppModel.h
//  uMWinSDK
//
//  Created by wangwei on 15-08-05.
//  Copyright (c) 2015年 uMWin Mobile Co. Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "publicconfuse.h"

@interface UMWSourceData : NSObject<NSCopying>

// 该应用的id（可以作为跟其他广告的区分）。
@property(nonatomic, retain, readonly)    NSString    *uMWstoreID;
// 应用名称
@property(nonatomic, retain, readonly)    NSString    *uMWname;
// 应用图标
@property(nonatomic, retain, readonly)    NSString    *uMWIconURL;
// 简短广告词
@property(nonatomic, retain, readonly)    NSString    *uMWadText;
//较为详细步骤提示
@property(nonatomic, retain, readonly)     NSString   *uMWtaskBrief;
//简短步骤提示
@property(nonatomic, retain, readonly)     NSString   *uMWtaskSteps;
// 过期时间
@property(nonatomic, retain, readonly)    NSDate      *uMWexpiredTime;
// 积分值。已经完成的任务，points为0。
@property(nonatomic, assign, readonly)    NSInteger   uMWpoints;
//用于应用内打开（不建议使用，应用内打开appStore经常出现空白页）
@property(nonatomic, assign, readonly)     NSInteger    uMWAppStoreID;
//应用在appStore的下载链接。(不要直接使用这个去下载，用户点击的时候调用下面的uMWinInstallSourceDataApp接口)
@property(nonatomic, retain, readonly)     NSString    *uMWDownloadURL;
//应用包名bundleID。
@property(nonatomic, retain, readonly)     NSString    *uMWBundleIdentifier;
//判断这个广告是否需要提审。(需要提审的就是快速任务)
@property(nonatomic, assign, readonly)     BOOL        uMWIsNeedReview;


//深度任务描述（如果此广告不是深度任务广告，则uMWMoreTask为nil，注意判断）。more tasks
/*
 {
 at: 16,  //开发者不用理这个参数
 adtext: "第二天 再次打开试用3分钟",   //追加任务广告语
 points: 2800,                     //追加任务积分
 etm: "60", //开发者不用理这个参数
 status: 0                         //0表示任务还没开始，1表示任务正在进行，2表示任务已经过期
 }
 */
@property(nonatomic, retain, readonly)     NSArray      *uMWMoreTasks;

//应用大小。app size
@property(nonatomic, retain, readonly)     NSString     *uMWsize;
// 搜索任务关键字
@property(nonatomic, retain, readonly)     NSString     *uMWkeyWord;
// 搜索任务的搜索排名
@property(nonatomic, retain, readonly)     NSString     *uMWRank;
// 剩余份数 【快速任务】
@property(nonatomic, retain, readonly)     NSString     *uMWBLC;
// 进行中的任务的剩余时间 【快速任务】
@property(nonatomic, retain, readonly)     NSString     *uMWRestTime;
// 任务是否进行中
@property(nonatomic, retain, readonly)     NSString     *uMWIsRunning;
// 目前获得该任务奖励的人数
@property(nonatomic, retain, readonly)     NSString     *uMWSuccessNum;

// !!!:获取积分墙的App广告列表-----有提审任务跟追加任务【源数据的接口】
//      param page: 请求的数据第几页
//      param count: 每页有多少个广告（比如设置的requestPage为1，adCountPage为3.那么数据就可以看成是每页3个应用的形式在服务器上，每次请求服务器就把对应页的3个应用返回）
//      param recievedBlock: 接收广告列表的block, 其中theNormalTasks的内容是 @[UMWSourceData, UMWSourceData...]; 获取列表失败, 在NSError里有记录，supplementTasks是追加任务跟theNormalTasks是同类型的内容。theNormalTasks中的元素UMWSourceData的uMWIsNeedReview为YES的时候是需要提审的，即用户完成了任务步骤后需要回来调用下面的uMWReview接口。调用下面的接口uMWBeginMoreTask来开始深度任务。
//
+ (void)uMWinRequestSourceData:(NSInteger)uMWinDataPage countPerPage:(NSInteger)countPerPage uMWinCallbackBlock:(void (^)(NSArray *theNormalTasks,NSArray *supplementTasks, NSError *error))callbackBlock;



// !!!: 安装积分墙中的APP【源数据的接口】
/*
    param uMWApp: 通过requestOffersOpenData获得的APP
    douCallback回调，code不为0的时候为开始任务失败。
    code{
     0:开始任务成功
     401: 网络不好
     2012: 任务被抢光
    }
 
 【重要】
    * 对于需要提审的任务（uMWIsNeedReview 为yes的任务，也就是快速任务），开始任务成功后在30分钟内必须完成任务。否则会视为自动放弃任务
    * 开始了一个快速任务后，是必须要做完这个任务后才能开始抢下一个快速任务。除非放弃当前抢到的任务
 */
+ (void)uMWinInstallSourceDataApp:(UMWSourceData *)uMWApp douCallback:(void (^)(NSInteger code))douCallback;

// !!!: 放弃任务
/* 
    抢到了一个快速任务后，如果想做其他的快速任务。则需要先放弃当前抢到得快速任务
 douCallback回调，code不为0的时候为放弃任务失败。
 code{
 0:放弃任务成功
 401: 网络不好
 }
 */
+ (void)uMWinGiveUpFastTask:(UMWSourceData *)uMWApp douCallback:(void (^)(NSInteger code))douCallback;

// !!!:提审【源数据的接口】
/*
 检查UMWSourceData的uMWIsNeedReview成员变量的值来判断是否需要提审
 status:0  提审成功，等待审核给分
 status:401 网络错误，没提审成功
 status:402 还没开始任务
 status:404 还没完成
 */
+ (void)uMWReview:(UMWSourceData *)uMWApp uMWinCallbackBlock:(void(^)(NSInteger status))callBack;

// !!!:开始追加任务【源数据的接口】
/*
 isSuccess:1  成功开始进行深度任务
 isSuccess:0  应用没安装，不能进行深度任务
 */
+ (void)uMWBeginMoreTask:(UMWSourceData *)uMWApp uMWinCallbackBlock:(void(^)(BOOL isSuccess))callBack;

@end
