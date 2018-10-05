/*
 * Car eye 车辆管理平台: www.car-eye.cn
 * Car eye 开源网址: https://github.com/Car-eye-team
 * CarEyeRtmpAPI.h
 *
 * Author: Wgj
 * Date: 2018-03-19 19:11
 * Copyright 2018
 *
 * CarEye RTMP推流库接口头文件
 * 实时推送数据时候支持最大8个通道的流
 */

#ifndef __CAREYE_PUSHER_H__
#define __CAREYE_PUSHER_H__

#include "CarEyeTypes.h"

// RTMP推流器句柄
#define CarEyeRTMPHandle void*

#ifdef __cplusplus
extern "C"
{
#endif

	/*
	* Comments: 使用有效的Key进行CarEye RTMP推流器的注册以便使用, 使用本系统前必须进行注册才能正常使用
	* Param key: 有效的密钥
	* Param packName: 针对Android系统的应用程序包名
	* @Return int CAREYE_NOERROR: 成功, 返回结果参考CarEyeError
	*/
#ifdef ANDROID
	CE_API int CE_APICALL CarEyeRTMP_Register(char* key, char* packName);
#else
	CE_API int CE_APICALL CarEyeRTMP_Register(char* key);
#endif

	/*
	* Comments: 注册推流状态事件
	* Param event: 获取推流状态的回调函数
	* @Return None
	*/
	CE_API void CE_APICALL CarEyeRTMP_RegisterStateChangedEvent(CarEyePusher_StateChanged event);

	/*
	* Comments: 获取当前通道的推流器是否已经连接到服务器并做好推流准备
	* Param channel: 通道号
	* @Return int 0未做好准备, 非0做好准备
	*/
	CE_API int CE_APICALL CarEyeRTMP_PusherIsReady(int channel);

	/*
	* Comments: 启动RTMP推流本地文件通道
	* Param svrip: 流媒体服务器IP地址或域名
	* Param port: 流媒体服务器端口号
	* Param Name: 推流的通道名
	* Param fileName: 要推流的本地文件路径 目前暂时支持MP4文件
	* Param startMs: 推流起始的毫秒数
	* Param endMs: 推流结束的毫秒数 endMs必须大于startMs, 否则推流失败, 当两个参数都为0时推送全文件
	* @Return int 大于等于0: 启动的推流通道号 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEyeRTMP_StartNativeFile(char* svrip, unsigned short port, char* name, char* fileName, int startMs, int endMs);

	/*
	* Comments: 推送流媒体数据到指定通道中
	* Param channel: 要推送的通道号
	* Param frame: 要推送的帧数据
	* @Return int 是否推送成功, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEyeRTMP_PushNativeData(int channel, CarEye_AV_Frame* frame);

	/*
	* Comments: 关闭指定的本地文件RTMP推流通道
	* Param channel: 已启动的RTMP推流通道号
	* @Return int 是否成功关闭, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEyeRTMP_StopNativeFile(int channel);

	/*
	* Comments: 创建一个直接推流的推流器
	* Param : None
	* @Return 成功返回推流器句柄，失败返回NULL
	*/
	CE_API CarEyeRTMPHandle CE_APICALL CarEyeRTMP_Create(void);

	/*
	* Comments: 设置直推推流器的状态回调函数
	* Param :
	* @Return void
	*/
	CE_API int CE_APICALL CarEyeRTMP_SetCallback(CarEyeRTMPHandle handle, CarEyeRTMP_CallBack callback, void *userptr);

	/*
	* Comments: 启动RTMP推流通道
	* Param handle: 创建成功的推流器句柄
	* Param url: 推流链接
	* Param mediaInfo: 要推流的媒体信息
	* @Return int CAREYE_NOERROR: 连接成功 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEyeRTMP_Connect(CarEyeRTMPHandle handle, const char* url, CarEye_MediaInfo*  mediaInfo);

	/*
	* Comments: RTMP直推推流器是否已链接
	* Param :
	* @Return void
	*/
	CE_API int CE_APICALL CarEyeRTMP_IsConnected(CarEyeRTMPHandle handle);
	
	/*
	* Comments: 关闭指定的RTMP推流通道
	* Param channel: 已启动的RTMP推流通道号
	* @Return int 是否成功关闭, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEyeRTMP_Release(CarEyeRTMPHandle handle);

	/*
	* Comments: 推送流媒体数据到指定通道中
	* Param channel: 要推送的通道号
	* Param frame: 要推送的帧数据
	* @Return int 是否推送成功, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEyeRTMP_PushData(CarEyeRTMPHandle handle, CarEye_AV_Frame* frame);

#ifdef __cplusplus
}
#endif

#endif
