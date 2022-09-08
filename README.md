# philosophers

#### [error] ./philo 

자다가 죽으면 자는 시간만큼 후에 깨어나서 죽음 & 포크 잡고 기다리다 죽어야 되는 시간 이후에 다으 포크를 잡고 죽는 문제

► 모니터링 스레드 생성 <a href='https://github.com/pearpearB/philosophers/commit/26113f33bc854e86fbb16b384fdc18bb1918585d'/> 8/29 commit <a />

-------------------

#### [error] ./philo_bonus 99 410 200 200 

특정 철학자가 죽고 난 후에도 다른 철학자의 상태가 출력됨

► 남은 프로세스들(철학자들)이 종료되기 전에 sem_post(print)를 해주어서 대기하고 있더 프린트 내용들이 출력되는 문제 -> kill_pid로 프로세스들을 다 종료시킨 후, sem_post(print) 해 주는 것으로 바꿈 <a href='https://github.com/pearpearB/philosophers/commit/3eb2beb177dfb37da2528bb0de2e646fbb50d66d'/> 9/04 commit <a />

-------------------

#### [error] ./philo_bonus 99 410 200 200 

죽는 철학자가 먹고 안 죽어야 되는데 죽음

► 죽는 철학자으 넘버를 출력해주느 함수의 위치 문제, 부모 프로세스에서 출력해주 있었음! (프로세스간 공유 불가) -> 자식에서 출력되도록 바꿈 <a href='https://github.com/pearpearB/philosophers/commit/f694a896911649987236b31cb40ebab7cea48448'/> 9/04 commit <a />

-------------------

#### [error] ./philo_bonus

죽는 시간이 10ms 넘게 밀림(20~40ms)

► 프로세스가 생성된 후 philo의 time_last_eat를 셋팅해주어서 밀린 시간으로 셋팅되는 문제 -> philo의 time_last_eat 셋팅 위치를 init_philo()로 바꿔줌 <a href='https://github.com/pearpearB/philosophers/commit/8e017ee5fba85a77b1dda5f0550c472b4a9d2e6e'/> 9/05 commit <a />

-------------------

#### [error] ./philo_bonus 100 440 200 200 3

죽으면 안되는데 먹다가 죽음

► 짝수 홀수 섞어서 먹어서 누군가가 포크를 뺏기고 죽음 -> 자식 프로세스 생성 시간이 밀리기 때문에 usleep에서 '짝수 시작시간 먹는 시간 * 0.5'로 바꿔줌 <a href='https://github.com/pearpearB/philosophers/commit/633e1474ce35eedfb5e5ce7e7f52e0fca1fa42a7'/> 9/05 commit <a />

-------------------

#### [error] ./philo_bonus 100 440 200 200 3

다 먹었는데 간헐적으로 종료가 안됨

► 정상종료된 친구들도 부모 프로세스 wait_process()에서 sem_post(print), sem_post(check_last_eat)해주기 <a href='https://github.com/pearpearB/philosophers/commit/d8738a258264dafd8e9ae95873132f3b7eeef88c'/> 9/05 commit <a />

