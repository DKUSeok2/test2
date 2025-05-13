/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32202698
*	    Student name : 오유석
*/

#include <string>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "sched.h"

class SPN : public Scheduler{
    private:
        struct compare{
            bool operator()(const Job& j1,const Job& j2){
                return j1.service_time>j2.service_time;
        }
       };
       std::priority_queue<Job,std::vector<Job>,compare> pq;

    public:
        SPN(std::queue<Job> jobs, double switch_overhead) : Scheduler(jobs, switch_overhead) {
            name = "SPN";
        }

        // 스케줄링 함수 
        int run() override {
            // job_queue_가 비어있지 않고, 현재 수행된 시간에 도착한 작업이 있다면 할당
            if(!job_queue_.empty() && job_queue_.front().arrival_time <= current_time_)
            {
                pq.push(job_queue_.front());
                job_queue_.pop();
            }
            // 할당된 작업이 없고, pq가 비어있지 않으면 작업 할당
            if (current_job_.name == 0 && !pq.empty()){
                current_job_ = pq.top();
                pq.pop();
            }

            // 현재 작업이 모두 완료되면
            if(current_job_.remain_time == 0){
                // 작업 완료 시간 기록
                current_job_.completion_time = current_time_;
                // 작업 완료 벡터에 저장
                end_jobs_.push_back(current_job_);

                // 남은 작업이 없으면 종료
                if (pq.empty()) return -1;
                
                // 새로운 작업 할당
                current_job_ = pq.top();
                pq.pop();
                // context switch 타임 추가
                current_time_ += switch_time_;
            }
            
            // 현재 작업이 처음 스케줄링 되는 것이라면
            if (current_job_.service_time == current_job_.remain_time){
                // 첫 실행 시간 기록
                current_job_.first_run_time = current_time_;
            }

            // 현재 시간 ++
            current_time_++;
            // 작업의 남은 시간 --
            current_job_.remain_time--;


            // 스케줄링할 작업명 반환
            return current_job_.name;
        }
};

class RR : public Scheduler{
    private:
        int time_slice_;
        int left_slice_;
        std::queue<Job> waiting_queue;
    public:
        RR(std::queue<Job> jobs, double switch_overhead, int time_slice) : Scheduler(jobs, switch_overhead) {
            name = "RR_"+std::to_string(time_slice);
            time_slice_ = time_slice; 
            left_slice_ = time_slice;
        }

        int run() override {
            // job_queue_가 비어있지 않고, 현재 수행된 시간에 도착한 작업이 있다면 waiting_queue에 작업 할당
            if(!job_queue_.empty() && job_queue_.front().arrival_time <= current_time_)
            {
                waiting_queue.push(job_queue_.front());
                job_queue_.pop();
            }

            // 할당된 작업이 없고, waiting_queue가 비어있지 않으면 작업 할당
            if (current_job_.name == 0 && !waiting_queue.empty()){
                current_job_ = waiting_queue.front();
                waiting_queue.pop();
                // left_slice_를 초기화
                left_slice_ = time_slice_;
            }

            // 현재 작업이 모두 완료되면
            if(current_job_.remain_time == 0){
                // 작업 완료 시간 기록
                current_job_.completion_time = current_time_;
                // 작업 완료 벡터에 저장
                end_jobs_.push_back(current_job_);

                // 남은 작업이 없으면 종료
                if (waiting_queue.empty()) return -1;
                
                // 새로운 작업 할당
                current_job_ = waiting_queue.front();
                waiting_queue.pop();
                left_slice_ = time_slice_;

                current_time_ += switch_time_;
                // context switch 타임 추가
            }

            // time slice가 모두 수행되게 된다면
            if(left_slice_ == 0){
                // context switch가 발생하지 않는 상황
                if(waiting_queue.empty()){
                    left_slice_ = time_slice_;

                }
                // context switch가 발생 할 때
                else{
                    // 현재 작업을 waiting_queue에 할당
                    waiting_queue.push(current_job_);
                    // waiting_queue의 front를 현재 작업에 할당
                    current_job_ = waiting_queue.front();
                    waiting_queue.pop();
                    left_slice_ = time_slice_;
                    // 문맥 교환이 일어났기 때문에 문맥 교환 시간 추가
                    current_time_ += switch_time_;
                }
            }
            // 현재 작업이 처음 스케줄링 되는 것이라면
            if (current_job_.service_time == current_job_.remain_time){
                // 첫 실행 시간 기록
                current_job_.first_run_time = current_time_;
            }

            // 현재 시간 ++
            current_time_++;
            // 작업의 남은 시간 --
            current_job_.remain_time--;
            // 타임슬라이스 수행
            left_slice_--;

            // 스케줄링할 작업명 반환
            return current_job_.name;
        }
                
};

class SRT : public Scheduler{
    private:
        struct compare { 
            bool operator()(const Job& j1, const Job& j2) {  // A에서 E가 들어오기 전에는 순서가 D, B 이지만 E가 들어오게 되면 remain_time이 같으므로 도착시간이 빠른 B가 우선순위를 가진다
                if(j1.remain_time != j2.remain_time)
                    return j1.remain_time > j2.remain_time; // remain_time이 다른 경우에는 해당 시점에서 작업의 남은 시간이 적은 작업이 우선순위를 가짐
                else
                    return j1.arrival_time > j2.arrival_time; // remain_time이 같은 경우에는 도착시간이 빠른 작업이 우선적으로 수행
            }
        };
        std::priority_queue<Job, std::vector<Job>, compare> pq;
    public:
        SRT(std::queue<Job> jobs, double switch_overhead) : Scheduler(jobs, switch_overhead) {
            name = "SRT";
        }

        int run() override {
            // 할당된 작업이 없고, job_queue가 비어있지 않으면 작업 할당
            if (current_job_.name == 0 && !job_queue_.empty()){
                current_job_ = job_queue_.front();
                job_queue_.pop();
            }

            // job_queue_가 비어있지 않고, 현재 수행된 시간에 도착한 작업이 있다면 pq에 작업 할당
            if(!job_queue_.empty() && job_queue_.front().arrival_time <= current_time_) { 
                pq.push(job_queue_.front());
                job_queue_.pop();
            }

            
            // 현재 작업이 모두 완료되면
            if(current_job_.remain_time == 0){
                // 작업 완료 시간 기록
                current_job_.completion_time = current_time_;
                // 작업 완료 벡터에 저장
                end_jobs_.push_back(current_job_);

                // 남은 작업이 없으면 종료
                if (pq.empty()) return -1;

                //새로운 작업 할당
                current_job_ = pq.top();
                pq.pop();

                // context switch 타임 추가
                current_time_ += switch_time_;
            }

            //현재 작업이 남아있고, pq가 비어있지 않을 때
            if(current_job_.remain_time != 0 && !pq.empty()){
                //현재 작업의 남은 시간이 pq.top의 남은시간 보다 많은 경우 -> 남은 시간이 적은 pq.top이 우선적으로 수행되어야 한다 (선점형)
                if(current_job_.remain_time > pq.top().remain_time){
                    // 새로운 작업 할당
                    pq.push(current_job_);
                    current_job_ = pq.top();
                    pq.pop();
                    // context switch 타임 추가
                    current_time_ += switch_time_;
                }
            }

            
            // 현재 작업이 처음 스케줄링 되는 것이라면
            if (current_job_.service_time == current_job_.remain_time){
                // 첫 실행 시간 기록
                current_job_.first_run_time = current_time_;
            }

            // 현재 시간 ++
            current_time_++;
            // 작업의 남은 시간 --
            current_job_.remain_time--;

            // 스케줄링할 작업명 반환
            return current_job_.name;
        }
};

class HRRN : public Scheduler{
    private:
        struct compare{
        double current_time_; // 구조체 내에서 current_time_을 사용하기 위한 변수 선언 (double 타입)

        bool operator()(const Job& j1,const Job& j2){
            double j1_ratio = ((current_time_-j1.arrival_time) + j1.service_time) / j1.service_time; // 작업 j1의 응답률
            double j2_ratio = ((current_time_-j2.arrival_time) + j2.service_time) / j2.service_time; // 작업 j2의 응답률
            if(j1_ratio != j2_ratio)
                return j1_ratio < j2_ratio; // 작업 j1과 j2의 응답률이 같지 않으면 응답률이 큰 j1이 우선순위를 가진다
            else
                return j1.arrival_time > j2.arrival_time; // 작업 j1과 j2의 응답률이 같으면 도착시간이 빠른 작업이 우선순위를 가진다
        }
       };
        std::vector<Job> jobs; // 벡터 선언
    public:
        HRRN(std::queue<Job> jobs, double switch_overhead) : Scheduler(jobs, switch_overhead) {
            name = "HRRN";

        }

        int run() override {
            // job_queue_가 비어있지 않고, 현재 수행된 시간에 도착한 작업이 있다면 벡터 jobs에 작업 할당
            if(!job_queue_.empty() && job_queue_.front().arrival_time <= current_time_)
            {
                jobs.push_back(job_queue_.front());
                job_queue_.pop();
            }
            
            compare cmp; // compare 구조체의 객체 cmp 선언
            cmp.current_time_ = current_time_; // cmp의 멤버 변수인 current_time_을 현재 시간으로 초기화

            // 벡터를 cmp에 따라 정렬
            std::sort(jobs.begin(), jobs.end(), cmp);


            // 할당된 작업이 없고, job_queue가 비어있지 않으면 작업 할당
            if (current_job_.name == 0 && !jobs.empty()){
                current_job_ = jobs.back();
                jobs.pop_back();
            }

            // 현재 작업이 모두 완료되면
            if(current_job_.remain_time == 0){
                // 작업 완료 시간 기록
                current_job_.completion_time = current_time_;
                // 작업 완료 벡터에 저장
                end_jobs_.push_back(current_job_);

                // 남은 작업이 없으면 종료
                if (jobs.empty()) return -1;
                
                // 새로운 작업 할당
                current_job_ = jobs.back();
                jobs.pop_back();
                // context switch 타임 추가
                current_time_ += switch_time_;
            }
            
            // 현재 작업이 처음 스케줄링 되는 것이라면
            if (current_job_.service_time == current_job_.remain_time){
                // 첫 실행 시간 기록
                current_job_.first_run_time = current_time_;
            }

            // 현재 시간 ++
            current_time_++;
            // 작업의 남은 시간 --
            current_job_.remain_time--;

            // 스케줄링할 작업명 반환
            return current_job_.name;
        }
};

// FeedBack 스케줄러 (queue 개수 : 4 / boosting 없음)
class FeedBack : public Scheduler{
    private:
        std::vector<std::queue<Job>> q; // 벡터 선언
        std::vector<int> time_slice_; // 타임슬라이스를 벡터로 선언
        int left_slice_;
        int tmp; // 현재 작업에 있는 작업이 어느 큐에서 넘어온건지 확인하는 변수
    public:
        FeedBack(std::queue<Job> jobs, double switch_overhead, bool is_2i) : Scheduler(jobs, switch_overhead) {
            if(is_2i){
                name = "FeedBack_2i";
            } else {
                name = "FeedBack_1";
            }
            q.resize(4); // 큐의 갯수가 4개
            if(is_2i){ 
                for (int i = 0; i < q.size(); i++)
                    time_slice_.push_back(1 << i); // timeslice가 2^i 일 때 쉬프트 연산을 사용하여 각각의 큐에 타임 슬라이스 값을 부여
            } else {
                for (int i = 0; i < q.size(); i++)
                    time_slice_.push_back(1); // 모든 큐의 타임슬라이스가 1
            }
        }
 
        int run() override {
            // job_queue가 비어있지 않고,  현재 수행된 시간에 도착한 작업이 있다면 첫번째 큐에 넣음
            if(!job_queue_.empty() && job_queue_.front().arrival_time <= current_time_){
                q[0].push(job_queue_.front());
                job_queue_.pop();
            }
            //할당된 작업이 없고, 4개의 큐가 모두 비어있지 않으면 작업 할당
            if(current_job_.name == 0 && (!q[0].empty()||!q[1].empty()||!q[2].empty()||!q[3].empty())){
                current_job_ = q[0].front();
                q[0].pop();
                left_slice_ = time_slice_[0];
                tmp = 0;
            }


            // 현재 작업이 모두 완료되면
            if(current_job_.remain_time == 0){
                // 작업 완료 시간 기록
                current_job_.completion_time = current_time_;
                // 작업 완료 벡터에 저장
                end_jobs_.push_back(current_job_);

                // 남은 작업이 없고, 모든 큐가 비어있다면 종료
                if (job_queue_.empty() && (q[0].empty()&&q[1].empty()&&q[2].empty()&&q[3].empty())) return -1;
                
                // 새로운 작업 할당
                if(!q[0].empty()||!q[1].empty()||!q[2].empty()||!q[3].empty()){ // 큐가 모두 비어있지 않다면
                    for(int i = 0; i < q.size(); i++){
                        if(!q[i].empty()){ // 큐를 차례대로 확인하면서 비어있지 않은 큐가 있다면 현재 작업에 넣어줌
                            current_job_ = q[i].front();
                            left_slice_ = time_slice_[i];
                            q[i].pop();
                            tmp = i;
                            break; // 비어있지 않은 큐를 만나서 작업을 수행하면 빠져나감
                        }
                    }
                }
                // context switch 타임 추가
                current_time_ += switch_time_;
            }

            
            if(left_slice_ == 0){
                if(tmp == 3 || (q[0].empty()&&q[1].empty()&&q[2].empty()&&q[3].empty())){ // 만약 우선순위가 제일 낮은 큐에서 온 작업이라면
                    q[tmp].push(current_job_); // 다시 해당 큐에 넣어줌
                } else { // 우선순위가 제일 낮지 않다면
                    q[tmp + 1].push(current_job_); // 우선순위가 하나 낮은 큐에 넣어줌
                }
                for(int i = 0; i < q.size(); i++){
                    if(!q[i].empty()){
                        if(current_job_.name != q[i].front().name){ // 현재 작업의 이름과 큐의 첫번째 작업의 이름이 다르다면 문맥교환이 발생
                            current_time_ += switch_time_;
                        }
                        current_job_ = q[i].front(); // 비어있지 않은 첫번째 큐의 첫번째 작업을 현재 작업으로 넣어준다
                        left_slice_ = time_slice_[i]; // left_slice_를 초기화
                        q[i].pop();
                        tmp = i;
                        break;
                    }
                }

            }
            // 현재 작업이 처음 스케줄링 되는 것이라면
            if (current_job_.service_time == current_job_.remain_time){
                // 첫 실행 시간 기록
                current_job_.first_run_time = current_time_;
            }

            // 현재 시간 ++
            current_time_++;
            // 작업의 남은 시간 --
            current_job_.remain_time--;
            //left_slice_ --
            left_slice_--;

            // 스케줄링할 작업명 반환
            return current_job_.name;
        }
};
