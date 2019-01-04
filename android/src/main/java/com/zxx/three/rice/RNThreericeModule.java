
package com.zxx.three.rice;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.widget.Toast;

import com.facebook.react.bridge.ActivityEventListener;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.ReadableMap;

import java.util.HashMap;

import fsa.wes.ddt.AdManager;
import fsa.wes.ddt.listener.Interface_ActivityListener;
import fsa.wes.ddt.listener.OffersWallDialogListener;
import fsa.wes.ddt.os.OffersManager;

public class RNThreericeModule extends ReactContextBaseJavaModule {

  private final ReactApplicationContext reactContext;
  private String rice_appId = "";
  private String rice_appSecret = "";
  private String rice_isEnableYYMMLog = "";

  public RNThreericeModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.reactContext = reactContext;

    ApplicationInfo appInfo = null;
    try {
        appInfo = reactContext.getPackageManager().getApplicationInfo(reactContext.getPackageName(), PackageManager.GET_META_DATA);
    } catch (PackageManager.NameNotFoundException e) {
        throw new Error(e);
    }
    if (!appInfo.metaData.containsKey("rice_appId")){
      throw new Error("meta-data rice_appId not found in AndroidManifest.xml");
    }
    this.rice_appId = appInfo.metaData.get("rice_appId").toString();

    if (!appInfo.metaData.containsKey("rice_appSecret")){
      throw new Error("meta-data rice_appSecret not found in AndroidManifest.xml");
    }
    this.rice_appSecret = appInfo.metaData.get("rice_appSecret").toString();

    if (!appInfo.metaData.containsKey("rice_isEnableYYMMLog")){
      throw new Error("meta-data rice_isEnableYYMMLog not found in AndroidManifest.xml");
    }
    this.rice_isEnableYYMMLog = appInfo.metaData.get("rice_isEnableYYMMLog").toString();
  }

  @Override
  public String getName() {
    return "RNThreerice";
  }

  @Override
  public void initialize() {
    super.initialize();

    // 自v6.3.0起，所有其他代码必须在初始化接口调用之后才能生效
    // 初始化接口，应用启动的时候调用，参数：appId, appSecret, isEnableYoumiLog
    AdManager.getInstance(reactContext).init(this.rice_appId, this.rice_appSecret, !this.rice_isEnableYYMMLog.equals("0"));
  }

  @Override
  public void onCatalystInstanceDestroy() {
    super.onCatalystInstanceDestroy();

    // 回收积分广告占用的资源
    OffersManager.getInstance(reactContext).onAppExit();
  }

  @ReactMethod
  public void openThreeRice(ReadableMap map){
    HashMap<String, Object> json = map.toHashMap();
    String style = "0";
    if(json.get("style") != null){
      style = String.valueOf(json.get("style"));
    }
    String isExitTip = "0";
    if(json.get("isExitTip") != null){
      isExitTip = String.valueOf(json.get("isExitTip"));
    }
    String userid = "0";
    if(json.get("userid") != null){
      userid = String.valueOf(json.get("userid"));
    }

    // 有米android 积分墙sdk 5.0.0之后支持定制浏览器顶部标题栏的部分UI
    // setOfferBrowserConfig(context);

    // 如果开发者使用积分墙的服务器回调,
    // 1.需要告诉sdk，现在采用服务器回调
    // 2.建议开发者传入自己系统中用户id（如：邮箱账号之类的）（请限制在50个字符串以内）
    // 3.务必在下面的OffersManager.getInstance(this).onAppLaunch();代码之前声明使用服务器回调

    OffersManager.getInstance(reactContext).setUsingServerCallBack(true);
    OffersManager.getInstance(reactContext).setCustomUserId(userid);

    // 如果使用积分广告，请务必调用积分广告的初始化接口:
    OffersManager.getInstance(reactContext).onAppLaunch();

    // 0全屏
    if(style.equals("0")){
      // 0退出不提示
      if(isExitTip.equals("0")){
        // 调用方式一：直接打开全屏积分墙
        OffersManager.getInstance(reactContext).showOffersWall();
      }else{
        // 调用方式二：直接打开全屏积分墙，并且监听积分墙退出的事件onDestory
        OffersManager.getInstance(reactContext).showOffersWall(new Interface_ActivityListener() {

          /**
           * 当积分墙销毁的时候，即积分墙的Activity调用了onDestory的时候回调
           */
          @Override
          public void onActivityDestroy(Context context) {
            Toast.makeText(context, "rice退出了", Toast.LENGTH_SHORT).show();
          }
        });
      }
    }else{
      final String isExitTipTemp = isExitTip;
      OffersManager.getInstance(reactContext).showOffersWallDialog(reactContext.getCurrentActivity(), new OffersWallDialogListener() {

        @Override
        public void onDialogClose() {
          if(!isExitTipTemp.equals("0")){
            Toast.makeText(reactContext, "rice对话框关闭了", Toast.LENGTH_SHORT).show();
          }else {

          }
        }
      });
    }
  }
}