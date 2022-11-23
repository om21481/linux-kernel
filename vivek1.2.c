#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>  
#include<pthread.h>
#include<sys/wait.h>
#include<math.h>
#include<time.h>


void  setting_sheduler_child_A(struct sched_param p1,int prio){
    p1.sched_priority=prio;
    // sched_setparam(prio,&p1);
}
void  setting_sheduler_child_B(struct sched_param p1,int prio){
    p1.sched_priority=prio;
    // sched_setparam(prio,&p1);
}
void  setting_sheduler_child_C(struct sched_param p1,int prio){
    p1.sched_priority=prio;
    // shed_setparam(prio,&p1);
}
void setting_spriority_child_A(){
    // int pid_a=0;
    struct sched_param paramA;
    setting_sheduler_child_A(paramA,2);
    paramA.sched_priority = 2;

    printf("%d in function\n",getpid());

    int a_check=sched_setscheduler(getpid(),SCHED_FIFO,&paramA);
    if(a_check==-1){
        perror("\nerror in sched_setscheduler in A");
        return;
    }


}


void setting_spriority_child_B(){
    int pid_b=0;
    struct sched_param paramB;
    setting_sheduler_child_B(paramB,5);
    paramB.sched_priority = 5;
    int a_check=sched_setscheduler(pid_b,SCHED_RR,&paramB);
    if(a_check==-1){
        perror("error in sched_setscheduler in B");
        return;
    }


}




void setting_spriority_child_C(){
    int pid_c=0;
    struct sched_param paramC;
    setting_sheduler_child_C(paramC,0);
    paramC.sched_priority = 0;
    int a_check=sched_setscheduler(pid_c,SCHED_OTHER,&paramC);
    if(a_check==-1){
        perror("error in sched_setscheduler in C");
        return;
    }
}


int main(){
    int k1=0;
    int k2=0;
    int k3=0;
        struct timespec start;
        struct timespec end;
        int c_str=clock_gettime(CLOCK_REALTIME, &start);

        pid_t pid_a=fork();
        // printf("%d pid in main",getpid());
        if(pid_a==-1){
            perror("fork is not executed");
            return 0;
        }
        else{
            if(pid_a==0){
            setting_spriority_child_A();
            char** arg = {NULL};
            k2=1;
            execvp("./bash.sh",arg);

            }
            else{
                wait(NULL);
                int c_end=clock_gettime(CLOCK_REALTIME, &end);

                double e=1000000000;
                long double e11=end.tv_nsec/e;
                long double s11=start.tv_nsec/e;
                long double total_time= (end.tv_sec+e11) -(start.tv_sec + s11);

                printf("Total Time taken by thread A t1 : %Lf \n", total_time);

                struct timespec start1;
                struct timespec end1;
                int c_str1=clock_gettime(CLOCK_REALTIME, &start1);




                pid_t pid_b=fork();
                if(pid_b==-1){
                    perror("fork is not executed");
                    return 0;
                }
                else{
                
                    if(pid_b==0){
                    setting_spriority_child_B();
                    char** arg = {NULL};
                    k3==2;
                    execvp("./bash.sh",arg);
                    }
                    else{
                        wait(NULL);

                        int c_end1=clock_gettime(CLOCK_REALTIME, &end1);

                        double e11=1000000000;
                        long double e1=end1.tv_nsec/e11;
                        long double s1=start1.tv_nsec/e11;
                        long double total_time= (end1.tv_sec+e1) -(start1.tv_sec + s1);
                        printf("Total Time taken by thread B t2 : %Lf \n", total_time);

                        struct timespec start2;
                        struct timespec end2;

                        int c_str2=clock_gettime(CLOCK_REALTIME, &start2);



                        pid_t pid_c=fork();
                        // printf("%d pid in main",getpid());
                        if(pid_c==-1){
                            perror("fork is not executed");
                            return 0;
                        }
                        else{
                        
                            if(pid_c==0){
                            setting_spriority_child_C();
                            char** arg = {NULL};
                            execvp("./bash.sh",arg);
                            k2=1;
                            }
                            else{
                                wait(NULL);
                                int c_end2=clock_gettime(CLOCK_REALTIME, &end2);
                                double e22=1000000000;
                                long double e2=end2.tv_nsec/e22;
                                long double s2=start2.tv_nsec/e22;
                                long double total_time= (end2.tv_sec+e2) -(start2.tv_sec + s2);

                                printf("Total Time taken by thread C t3 : %Lf \n", total_time);
                                
                            }
                        }

                    }
                }

            }
        }

    // if(k2==1){

    //     // printf("fiovbhj\n");
    //     pid_t pid_b=fork();
    //     if(pid_b==-1){
    //         perror("fork is not executed");
    //         return 0;
    //     }
    //     else{
    //         if(pid_b==0){
    //         setting_spriority_child_B();
    //         char** arg = {NULL};
    //         k3==2;
    //         execvp("./bash.sh",arg);
    //         }
    //     }
    // }
    // if(k3==2){
    //     printf("something new\n");
    //     pid_t pid_c=fork();
    //     // printf("%d pid in main",getpid());
    //     if(pid_c==-1){
    //         perror("fork is not executed");
    //         return 0;
    //     }
    //     else{
    //         if(pid_c==0){
    //         setting_spriority_child_C();
    //         char** arg = {NULL};
    //         execvp("./bash.sh",arg);
    //         k2=1;
    //         }
    //     }


    // }



    return 0;
}
