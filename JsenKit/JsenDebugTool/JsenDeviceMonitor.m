//
//  JsenDeviceMonitor.m
//  JsenKit
//
//  Created by WangXuesen on 2017/8/1.
//  Copyright © 2017年 WangXuesen. All rights reserved.
//

#import "JsenDeviceMonitor.h"
#import <mach/mach.h>
#import <sys/sysctl.h>


@implementation JsenDeviceMonitor

+ (void)jsen_deviceBatter:(JsenDeviceBatterInfo)info {
    UIDevice *device = [UIDevice currentDevice];
    device.batteryMonitoringEnabled = YES;
    UIDeviceBatteryState state = device.batteryState;
    NSUInteger batterLevel = (NSUInteger)(device.batteryLevel * 100);
    info(batterLevel,state);
    device.batteryMonitoringEnabled = NO;
}

+ (void)jsen_deviceCPUsage:(JsenDeviceCPUsage)sage {
   
    kern_return_t kr;
    task_info_data_t tinfo;
    mach_msg_type_number_t task_info_count;
    
    task_info_count = TASK_INFO_MAX;
    kr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)tinfo, &task_info_count);
    if (kr != KERN_SUCCESS) {
        sage(-1);
        
        return;
    }
    
    task_basic_info_t      basic_info;
    thread_array_t         thread_list;
    mach_msg_type_number_t thread_count;
    
    thread_info_data_t     thinfo;
    mach_msg_type_number_t thread_info_count;
    
    thread_basic_info_t basic_info_th;
    uint32_t stat_thread = 0; // Mach threads
    
    basic_info = (task_basic_info_t)tinfo;
    
    // get threads in the task
    kr = task_threads(mach_task_self(), &thread_list, &thread_count);
    if (kr != KERN_SUCCESS) {
        sage(-1);
        
        return;
    }
    if (thread_count > 0)
        stat_thread += thread_count;
    
    long tot_sec = 0;
    long tot_usec = 0;
    float tot_cpu = 0;
    int j;
    
    for (j = 0; j < thread_count; j++)
    {
        thread_info_count = THREAD_INFO_MAX;
        kr = thread_info(thread_list[j], THREAD_BASIC_INFO,
                         (thread_info_t)thinfo, &thread_info_count);
        if (kr != KERN_SUCCESS) {
            sage(-1);
            
            return;
        }
        
        basic_info_th = (thread_basic_info_t)thinfo;
        
        if (!(basic_info_th->flags & TH_FLAGS_IDLE)) {
            tot_sec = tot_sec + basic_info_th->user_time.seconds + basic_info_th->system_time.seconds;
            tot_usec = tot_usec + basic_info_th->system_time.microseconds + basic_info_th->system_time.microseconds;
            tot_cpu = tot_cpu + basic_info_th->cpu_usage / (float)TH_USAGE_SCALE * 100.0;
        }
        
    } // for each thread
    
    kr = vm_deallocate(mach_task_self(), (vm_offset_t)thread_list, thread_count * sizeof(thread_t));
    assert(kr == KERN_SUCCESS);
    
    sage(tot_cpu);
    
}

// 获取当前设备可用内存(单位：MB）
+ (double)jsen_availableMemory {
    vm_statistics_data_t vmStats;
    mach_msg_type_number_t infoCount =HOST_VM_INFO_COUNT;
    kern_return_t kernReturn = host_statistics(mach_host_self(),
                                              HOST_VM_INFO,
                                              (host_info_t)&vmStats,
                                              &infoCount);
    
    if(kernReturn != KERN_SUCCESS) {
        return NSNotFound;
    }
    
    return ((vm_page_size *vmStats.free_count) / 1024.0) / 1024.0;
}

//获取当前任务所占用的内存（单位：MB）
+ (double)jsen_usedMemory {
    task_basic_info_data_t taskInfo;
    mach_msg_type_number_t infoCount =TASK_BASIC_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(),
                                         TASK_BASIC_INFO,
                                         (task_info_t)&taskInfo,
                                         &infoCount);
    
    if(kernReturn != KERN_SUCCESS
       ) {
        return NSNotFound;
    }
    
    return taskInfo.resident_size / 1024.0 / 1024.0;}

@end
