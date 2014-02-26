/**
 * @file     Common.h
 * @date     2013-12-15
 * @author   cnagune (blog@cnagune.pe.kr)
 * @brief    공통적인 상수나 함수 등을 담은 부분
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#if defined(ANDROID) || defined(__ANDROID__)
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "test", __VA_ARGS__) 
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "test", __VA_ARGS__) 
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , "test", __VA_ARGS__) 
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , "test", __VA_ARGS__) 
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "test", __VA_ARGS__) 
#else
#define LOGV(...) printf("test LogV: ", __VA_ARGS__);
#define LOGD(...) printf("test LogD: ", __VA_ARGS__);
#define LOGI(...) printf("test LogI: ", __VA_ARGS__);
#define LOGW(...) printf("test LogW: ", __VA_ARGS__);
#define LOGE(...) printf("test LogE: ", __VA_ARGS__);
#endif


#ifdef __cplusplus 
extern "C" {
#endif


/*********************************************************
 * 상수 부분
 *********************************************************/
#define CACHE_LINE_SIZE (64)    /// 캐시 라인 크기 (64로 고정)


#ifdef __cplusplus 
}
#endif

#endif  /* __COMMON_H__ */

