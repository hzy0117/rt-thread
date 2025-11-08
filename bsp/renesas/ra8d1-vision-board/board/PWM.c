#include <rtdevice.h>
#include <rtthread.h>

#define PWM_DEV_NAME        "pwm12"  // PWM 设备名称
#define PWM_DEV_CHANNEL     0       // PWM通道

//PWM 设备句柄 
struct rt_device_pwm *pwm_dev = RT_NULL;     

//PWM周期和占空比，单位为纳秒ns
rt_uint32_t period, pulse;

void PWM_init(void){

    period = 40000;    
    pulse = 12000 ;   

    // 查找设备
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL){
        rt_kprintf("can't find pwm device: %s\n", PWM_DEV_NAME);
        return;
    }

    // 设置PWM周期和脉冲宽度默认值
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
}


//正在推进部分
/*
void PWM_THREAD_entry(double out){
    while(1){
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, period*out);
        rt_kprintf("set pwm %lf \n",period*out);
    }
}

static void PWM_MIAN(void){
    rt_thread_t tid1;
    tid1 = rt_thread_create("PWM_THREAD",PWM_THREAD_entry,out,1024,18,5);

    if(tid1 != RT_NULL){
        rt_thread_startup(tid1);
    }
    else(){
        rt_kprintf("PWM_THREAD creat failed!\n");
    }
}
*/

INIT_APP_EXPORT(PWM_init);