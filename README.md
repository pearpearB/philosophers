# philosophers


[error] philo_bonus 99 410 200 200 

특저 철학자가 죽고 난 후에도 다른 철학자의 상태가 출력됨

다르 프로세스들(철학자들)이 종료되기 전에 sem_post(print)를 해주어서 대기하고 있더 프린트 내용들이 출력되는 문제 -> kill_pid로 프로세스들을 다 종료시킨 후, sem_post(print) 해 주는 것으로 바꿈


[error] philo_bonus 99 410 200 200 

죽는 철학자가 먹고 안 죽어야 되는데 죽음

죽는 철학자으 넘버를 출력해주느 함수의 위치 문제, 부모 프로세스에서 출력해주 있었음! (프로세스간 공유 불가) -> 자식에서 출력되도록 바꿈


[error] philo_bonus

죽는 시간이 10ms 넘게 밀림(20~40ms)

프로세스가 생성된 후 philo의 time_last_eat를 셋팅해주어서 밀린 시간으로 셋팅되는 문제 -> philo의 time_last_eat 셋팅 위치를 init_philo()로 바꿔줌
