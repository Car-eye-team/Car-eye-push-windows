/*
* Car eye 车辆管理平台: www.car-eye.cn
* Car eye 开源网址: https://github.com/Car-eye-team
* CarEyeRtmpAPI.h
*
* Author: Wgj
* Date: 2018-03-19 19:11
* Copyright 2018
*
* CarEye RTSP/RTMP推流库接口头文件
* 实时推送数据时候支持最大8个通道的流
*/

#ifndef __CAREYE_PUSHER_H__
#define __CAREYE_PUSHER_H__

#ifdef _WIN32
#define CE_API  __declspec(dllexport)
#define CE_APICALL  __stdcall
#else
#define CE_API
#define CE_APICALL 
#endif

// 目前最多支持8个通道同时推流
#define MAX_CHN			8

// 本接口库错误码定义
typedef enum __CarEye_Error__
{
	// 无错误, 成功的
	CAREYE_NOERROR = 0,
	// 不支持的功能, 未实现的
	CAREYE_UNSUPPORTED = -1,
	// 系统初始化失败
	CAREYE_INITFAIL = -2,
	// 无推流通道可申请了
	CAREYE_NOCHANNEL = -3,
	// 创建推流器或其他对象失败
	CAREYE_CREATE_FAIL = -4,
	// 无效的输入参数
	CAREYE_INVALID_PARAM = -5,
	// 鉴权错误
	CAREYE_AUTH = -6,
	// 发送失败
	CAREYE_SEND_FAILE = -7,
}CarEyeError;

// 推流器类型定义
typedef enum __PUSHER_TYPE__
{
	// 直接推送RTSP数据流的推送器
	PUSHER_RTSP = 0,
	// 推送本地文件RTSP流的推送器
	PUSHER_NATIVEFILE_RTSP,
	// 推送RTMP数据流的推送器
	PUSHER_RTMP,
	// 推送本地文件RTMP流的推送器
	PUSHER_NATIVEFILE_RTMP,
}CarEyePusherType;

// 视频编码类型定义
typedef enum __VIDEO_CODE_TYPE__
{
	// H264编码
	CAREYE_VCODE_H264 = 0x1C,
	// H265编码
	CAREYE_VCODE_H265 = 0x48323635,
	// MJPEG编码
	CAREYE_VCODE_MJPEG = 0x08,
	// MPEG4编码
	CAREYE_VCODE_MPEG4 = 0x0D,
}CarEye_VCodeType;

// 音频编码类型定义
typedef enum __AUDIO_CODE_TYPE__
{
	// AAC编码
	CAREYE_ACODE_AAC = 0x15002,
	// G711 Ulaw编码
	CAREYE_ACODE_G711U = 0x10006,
	// G711 Alaw编码
	CAREYE_ACODE_G711A = 0x10007,
	// G726编码
	CAREYE_ACODE_G726 = 0x1100B,
}CarEye_ACodeType;

// 要推流的媒体信息结构体
typedef struct __MEDIA_INFO_T
{
	// 视频编码类型
	CarEye_VCodeType VideoCodec;
	// 视频帧率, 一般为25
	unsigned int VideoFps;

	// 音频编码类型
	CarEye_ACodeType AudioCodec;
	// 音频采样率, 录制人声一般为8000
	unsigned int AudioSamplerate;
	// 音频通道数, 一般选择为1
	unsigned int AudioChannel;
	// 音频采样率, 采样精度
	unsigned int AudioBitsPerSample;
}CarEye_MediaInfo;

// 视频帧类型定义
typedef enum __VIDEO_FRAME_TYPE__
{
	// I帧
	VIDEO_FRAME_I = 0x01,
	// P帧
	VIDEO_FRAME_P = 0x02,
	// B帧
	VIDEO_FRAME_B = 0x03,
	// JPEG
	VIDEO_FRAME_J = 0x04,
}CarEyeVideoFrameType;

// 视频帧标识
#define CAREYE_VFRAME_FLAG	0x00000001
// 音频帧标识
#define CAREYE_AFRAME_FLAG	0x00000002

// 媒体帧信息结构定义
typedef struct __CAREYE_AV_Frame_T
{
	// 帧类型标识 CAREYE_VFRAME_FLAG或者CAREYE_AFRAME_FLAG
	unsigned int	FrameFlag;
	// 帧的数据长度
	unsigned int	FrameLen;
	// 视频帧类型, 参考CarEyeVideoFrameType定义
	unsigned int	VFrameType;
	// 数据缓冲区
	unsigned char	*Buffer;
	// 时间戳总秒数
	unsigned int	Second;
	// 时间戳秒数无法精确的微秒数, 非总微秒数, 与Second结合形成精确时间
	unsigned int	USecond;
}CarEye_AV_Frame;

// 推流器状态定义
typedef enum __CAREYE_STATE_TYPE__
{
	// 正在连接服务器中
	CAREYE_STATE_CONNECTING = 1,
	// 已成功连接到服务器
	CAREYE_STATE_CONNECTED = 2,
	// 服务器连接失败
	CAREYE_STATE_CONNECT_FAILED = 3,
	// 推流异常中断, 此时应该停止推流或者重新启动推流器了...
	CAREYE_STATE_CONNECT_ABORT = 4,
	// 正在推流中
	CAREYE_STATE_PUSHING = 5,
	// 与服务器断开链接
	CAREYE_STATE_DISCONNECTED = 6,
	// 本地文件推流已完成
	CAREYE_STATE_FILE_FINISHED = 7,
	// 未知错误
	CAREYE_STATE_ERROR = 0xFF,
}CarEyeStateType;

/*
* Comments: 推流器状态变化通知回调函数声明
* Param channel: 推流器的通道号
* Param state: 实时状态
* Param type: 推流器类型
* @Return int
*/
typedef int(*CarEyePusher_StateChanged)(int channel, CarEyeStateType state, CarEyePusherType type);

#ifdef __cplusplus
extern "C"
{
#endif

	/*
	* Comments: 使用有效的Key进行CarEye推流器的注册以便使用, 使用本系统前必须进行注册才能正常使用
	* Param key: 有效的密钥
	* Param packName: 针对Android系统的应用程序包名
	* @Return int CAREYE_NOERROR: 成功, 返回结果参考CarEyeError
	*/
#ifdef ANDROID
	CE_API int CE_APICALL CarEye_Register(char* key, char* packName);
#else
	CE_API int CE_APICALL CarEye_Register(char* key);
#endif

	/*
	* Comments: 注册推流状态事件
	* Param event: 获取推流状态的回调函数
	* @Return None
	*/
	CE_API void CE_APICALL CarEye_RegisterStateChangedEvent(CarEyePusher_StateChanged event);

	/*
	* Comments: 启动RTSP推流通道 推流地址以三个参数进行组合: rtsp://svrip:port/name
	* Param svrip: 流媒体服务器IP地址或域名
	* Param port: 流媒体服务器端口号
	* Param name: 推流的sdp名
	* Param mediaInfo: 要推流的媒体信息
	* @Return int 大于等于0: 启动的推流通道号 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StartRTSPPusher(char* svrip, unsigned short port, char* name, CarEye_MediaInfo mediaInfo);

	/*
	* Comments: 关闭指定的RTSP推流通道
	* Param channel: 已启动的RTSP推流通道号
	* @Return int 是否成功关闭, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StopRTSPPusher(int channel);

	/*
	* Comments: 获取当前通道的推流器是否已经连接到服务器并做好推流准备
	* Param channel: 通道号
	* @Return int 0未做好准备, 非0做好准备
	*/
	CE_API int CE_APICALL CarEye_PusherIsReady(int channel);

	/*
	* Comments: 启动RTSP推流本地文件通道 推流地址以三个参数进行组合: rtsp://svrip:port/name
	* Param svrip: 流媒体服务器IP地址或域名
	* Param port: 流媒体服务器端口号
	* Param name: 推流的sdp名
	* Param fileName: 要推流的本地文件路径 目前暂时支持MP4文件
	* Param startMs: 推流起始的毫秒数
	* Param endMs: 推流结束的毫秒数 endMs必须大于startMs, 否则推流失败, 当两个参数都为0时推送全文件
	* @Return int 大于等于0: 启动的推流通道号 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StartNativeFileRTSP(char* svrip, unsigned short port, char* name, char* fileName, int startMs, int endMs);

	/*
	* Comments: 关闭指定的本地文件RTSP推流通道
	* Param channel: 已启动的RTSP推流通道号
	* @Return int 是否成功关闭, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StopNativeFileRTSP(int channel);

	/*
	* Comments: 启动RTMP推流通道
	* Param svrip: 流媒体服务器IP地址或域名
	* Param port: 流媒体服务器端口号
	* Param name: 推流的通道名
	* Param mediaInfo: 要推流的媒体信息
	* @Return int 大于等于0: 启动的推流通道号 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StartRTMPPusher(char* svrip, unsigned short port, char* name, CarEye_MediaInfo mediaInfo);

	/*
	* Comments: 关闭指定的RTMP推流通道
	* Param channel: 已启动的RTMP推流通道号
	* @Return int 是否成功关闭, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StopRTMPPusher(int channel);

	/*
	* Comments: 启动RTMP推流本地文件通道
	* Param svrip: 流媒体服务器IP地址或域名
	* Param port: 流媒体服务器端口号
	* Param name: 推流的通道名
	* Param fileName: 要推流的本地文件路径 目前暂时支持MP4文件
	* Param startMs: 推流起始的毫秒数
	* Param endMs: 推流结束的毫秒数 endMs必须大于startMs, 否则推流失败, 当两个参数都为0时推送全文件
	* @Return int 大于等于0: 启动的推流通道号 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StartNativeFileRTMP(char* svrip, unsigned short port, char* name, char* fileName, int startMs, int endMs);

	/*
	* Comments: 关闭指定的本地文件RTMP推流通道
	* Param channel: 已启动的RTMP推流通道号
	* @Return int 是否成功关闭, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StopNativeFileRTMP(int channel);

	/*
	* Comments: 推送流媒体数据到指定通道中
	* Param channel: 要推送的通道号
	* Param frame: 要推送的帧数据
	* @Return int 是否推送成功, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_PushData(int channel, CarEye_AV_Frame* frame);

#ifdef __cplusplus
}
#endif

#endif