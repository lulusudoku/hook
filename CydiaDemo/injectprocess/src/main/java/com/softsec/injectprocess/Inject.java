package com.softsec.injectprocess;

import android.util.Log;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

/**
 * Created by LCX on 2016/5/30.
 */
public class Inject implements IXposedHookLoadPackage {
    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if (!loadPackageParam.packageName.equals("com.example.duanxinqunfa")) {
            Log.d("Inject", "Init Xposed!");
            System.load("/data/local/tmp/libhide.so");
            System.load("/data/local/tmp/libhookjni.so");
        }
    }
}
