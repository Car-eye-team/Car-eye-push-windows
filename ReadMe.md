# CarEyePusher推流库
car-eye-push 是car-eye团队开发的一个推流库，支持RTSP,RTMP推送，支持多通道推送数据，支持windows android，linux等多种系统，支持ARM,x86，x64和mips多种架构   
API 接口简单，方便快速移植到自己的系统中。
### 接口说明：
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

## Demo实现功能
* 推送本地MP4文件指定时间段到服务器
* 推送H264流媒体数据到服务器
* 多通道同时推送MP4文件以及H264流媒体数据到服务器

## 联系我们
car-eye车辆管理平台：www.car-eye.cn; car-eye开源平台网址：https://github.com/Car-eye-team 有关car-eye 问题咨询加QQ群590411159。

