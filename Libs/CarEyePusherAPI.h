/*
 * CarEyePusherAPI.h
 *
 * Author: Wgj
 * Date: 2018-03-05 20:02
 *
 * CarEye推流库接口头文件
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
	CarEye_NoError = 0,
	// 不支持的功能, 未实现的
	CarEye_Unsupported = -1,
	// 系统初始化失败
	CarEye_InitFail = -2,
	// 无推流通道可申请了
	CarEye_NoChannel = -3,
	// 创建推流器或其他对象失败
	CarEye_CreateFail = -4,
	// 无效的输入参数
	CarEye_InvalidParam = -5,
}CarEyeError;

// 推流器类型定义
typedef enum __PUSHER_TYPE__
{
	// 直接推送RTSP数据流的推送器
	Pusher_RTSP = 0,
	// 推送本地文件RTSP流的推送器
	Pusher_NativeFileRTSP,
	// 推送RTMP数据流的推送器
	Pusher_RTMP,
	// 推送本地文件RTMP流的推送器
	Pusher_NativeFileRTMP,
}CarEyePusherType;

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
	// 时间戳秒数无法精确的微秒数, 非总微秒数, 与u32TimestampSec结合形成精确时间
	unsigned int	USecond;
}CarEye_AV_Frame;


#ifdef __cplusplus
extern "C"
{
#endif

	/*
	* Comments: 启动RTSP推流通道 推流地址以三个参数进行组合: rtsp://svrip:port/name
	* Param svrip: 流媒体服务器IP地址或域名
	* Param port: 流媒体服务器端口号
	* Param name: 推流的sdp名
	* @Return int 大于等于0: 启动的推流通道号 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StartRTSPPusher(char* svrip, unsigned short port, char* name);

	/*
	* Comments: 关闭指定的RTSP推流通道
	* Param channel: 已启动的RTSP推流通道号
	* @Return int 是否成功关闭, 状态码参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StopRTSPPuser(int channel);

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
	* @Return int 大于等于0: 启动的推流通道号 小于0错误编号参考CarEyeError
	*/
	CE_API int CE_APICALL CarEye_StartRTMPPusher(char* svrip, unsigned short port, char* name);

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