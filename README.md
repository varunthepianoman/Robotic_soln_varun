# Robotic_soln_varun: Solution to Robotic_HW
# License
Creative Commons, All Rights Reserved
# Requirements
- ROS2 Humble. Instructions:  (Ubuntu): [https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html)
- Numpy
# Installation & Run Instructions
- clone repo locally:
```
git clone github.com/varunthepianoman/Robotic_soln_varun
```
- Source the setup script:
```
# Replace ".bash" with your shell if you're not using bash
# Possible values are: setup.bash, setup.sh, setup.zsh
source /opt/ros/humble/setup.bash
```
- Build packages: In the repo's root directory:
```
colcon build
```
- In a new terminal, Navigate to this repo's root directory, then source workspace with:
```
source install/setup.bash
```
- Run the Python Bringup Script:
```
ros2 run sensor_package_cpp bringup_py.py
```
- In another terminal, after sourcing the workspace, Run the C++ Bringup Script:
```
ros2 run sensor_package_cpp bringup_executable
```
- Log messages should be printed to the screen; see output_cpp.png and output_py.png for examples on the author's machine.
- To shutdown, in both running terminals enter: 
```
Ctrl + \
```

# Design Notes

## Testing & Dev Technical Specs:
- Mac OS 12
- Ubuntu 22.04.4 with VirtualBox 7 (4GB RAM, 2 cores, 25GB space)
- ROS 2 Humble
- All nodes run in Terminal
- Editors: Vim & CLion
- debuggers used: gdb & pdb.
## ROS Environment
- The repository represents a single workspace, with no overlaying/underlaying beyond this
- 2 relevant packages:
	- sensor_package_cpp with all Python and CPP code
		- build type: ament_cmake (with ament_cmake_python dependency so that we can run Python and CPP nodes in the same package)
	- custom_interfaces with my custom services and messages.
		- build type: ament_cmake
# Relevant Files:
Please note that all code is in src/sensor_package_cpp and src/custom_interfaces folder.
### ROS2 Nodes
- Launch Node for Python Scripts: 
	- src/sensor_package_cpp/sensor_package_cpp/bringup_py.py

- Sensor:
	- src/sensor_package_cpp/sensor_package_cpp/submodules/sensor.py
- Service for Sensor: 
	- src/sensor_package_cpp/sensor_package_cpp/submodules/sensor_service.py
- Launch Node for C++ Scripts:
	- src/sensor_package_cpp/src/bringup_cpp.cpp
- Sensor Client: 
	- src/sensor_package_cpp/include/sensor_package_cpp/sensor_client.hpp
- Sensor Publisher: 
	- src/sensor_package_cpp/include/sensor_package_cpp/sensor_read_publisher.hpp
- Sensor Subscriber: 
	- src/sensor_package_cpp/include/sensor_package_cpp/sensor_subscriber.hpp
- CMakeLists:
	- src/sensor_package_cpp/CMakeLists.txt
- package.xml:
	-  src/sensor_package_cpp/package.xml

### Custom Interface
- Single Sensor Single Sample Message:
	- src/custom_interfaces/msg/SensorSample.msg
- Single Sensor Many Samples Service: 
	- src/custom_interfaces/srv/SensorRead.srv
- Both Sensor SamplesMessage to Publish: 
	- src/custom_interfaces/msg/SensorReadCombined.msg
- CMakeLists:
	- src/custom_interfaces/CMakeLists.txt
- package.xml:
	-  src/custom_interfaces/package.xml
### Note
There may be other files here, including the all-python prototype package sensor_package, but the above files are the relevant ones for the final solution.
# Overview of Control Flow
- execute node `bringup_py.py`:
	- start 2 `SensorService` objects, one for each sensor. For each `SensorService`, in constructor:
		- Initiate `Sensor`
			- Initiate service `socket`
			- In a new thread, `run` this `Sensor`
		- In a new thread, start `query_for_samples` to my `Sensor`.
		- Create my service `srv` so I can communicate with the Client I am associated with.
	- Initiate `MultiThreadedExecutor executor`.
	- Add each `SensorService` node to our `executor`.
	- `Spin` our `executor`
- execute node `bringup_cpp.cpp`:
	- Initiate `MultiThreadedExecutor executor`.
	-  make 2 `SensorClient` objects, one for each sensor. For each:
		- Create my `client` with a new callback group.
	- make `SensorReadPublisher`, our timer publisher.
		- Create Publisher object to publish to a topic.
		- Create a wall-timer to call the Publisher object every 2ms.
	- make `make SensorReadSubscriber`, to subscribe to the topic of our publisher.
		- Create Subscription to topic.
	- Add all 4 nodes to our executor
	- `spin` our `executor`.
- Ongoing Processes governed by nodes:
	- Our `SensorService` object continuously queries for new data and updates its `data_reservoir`
	- Every 2ms, our timer publisher publishes a new message containing data from both of our sensors.
		- Send a request for data from both sensors via my clients for each of them
		- Generate combined message publishing, filling in data from both Client Responses.
		- Publish the combined message to my topic.
# Class & File Documentation
```python
class SensorService(Node):
	- MEMBER ATTRIBUTES:
	address: str # IP Address of the socket interface for our sensor
	port: int # port of the socket interface for our sensor 
	sampling_rate: int # Sampling rate of our sensor
	_delay: float  # delay of our sensor
	sensor_id: int # 1 or 2: Which sensor
	number_of_samples: int 
		# How many samples to query the sensor on each run. 
		# Default: 1 for sensor1, 8 for sensor2.
	data_reservoir: deque(maxlen=buffer_size) # Data reservoir is a deque reservoir of the last buffer_size samples.
	sensor: Sensor(address, port, sampling_rate, _delay, sensor_id) # The sensor we are a service for, constructed in my constructor: address, port, sampling rate and delay defined in SensorService constructor args. 
	client_sock: socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Client socket for our sensor
	srv: rclpy.service.Service # My service
	- MEMBER FUNCTIONS
	def sensor_read_callback(self, request, response) -> ~SrvTypeResponse:
		# Callback for my service, requested when client needs new sensor data. Takes a request and response object, fills out response and returns it.
		# Pops request.num_samples from deque while there is still data to be given
		# returns a response with the relevant readings as an array of SensorSamples
	def query_for_samples(self) -> None:
		# Continuously queries for self.number_of_samples samples using a socket interface.
		# Closes socket on termination.
```
```
	- Runs Client Socket in a new Thread
	- Runs in a Reentrant Callback Group
		- Callback groups: Services can run in parallel so put each in its own callback group.  
		- Use ReentrantCallbackGroup instead of MutuallyExclusive so that the continous query_for_samples doesn't block this init and the service callback.
```


```python
class Sensor(Thread):
	- MEMBER ATTRIBUTES
	address: str,  # My IP Address
	port: int,  # My port
	sampling_rate: int,  # My sampling rate
	overhead_delay: float,  # My delay
	id: int # Either 1 or 2: Which sensor am I
	server_sock: socket.socket(socket.AF_INET, socket.SOCK_STREAM) # My server socket to communicate with the ServiceSensor for me.
	- MEMBER FUNCTIONS
	def recive(self, buffer_size: int)->int:  
	    # Read a buffer size from the socket
    def send(self, data: np.ndarray)->bool:  
	    # Send the data to the client
    def run(self)->None:
	    # Run the sensor sampling, and send back to SensorService via socket.
```


```c++
class SensorClient: public rclcpp::Node {
	- MEMBER ATTRIBUTES
	private:  
    rclcpp::CallbackGroup::SharedPtr callback_group; // my callback group
    rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedPtr sensor_client;  // the client I am a wrapper for
    int sensor_id;  // which sensor am I associated with
    int num_samples; // how many samples to query. Note that this may be different that the corresponding number of samples due to latency and possibility of generating multiple sample queries in a single cycle, and is defaulted to 8 for sensor1 and 32 for sensor2. Generally, we probably want to pull all samples present from the data_reservoir, but keep this variable in case not.
    public:
    SensorClient(std::string name, int sensor_id, int num_samples) // Constructor
	    // Initialize Node base class with name, private attributes sensor_id, num_samples
	    // Create callback group:
		    // The clients are called within the publisher, so they must be in different Callback Groups than Publisher to avoid deadlock.  
			// Clients 1 and 2 can be called in parallel, so place them in different Callback Groups as well.  
			// Favoring MutuallyExclusive over Reentrant as it is safer: We then won't have two queries accessing same server data_reservoir.
		// Initiate sensor_client with callback_group
	- MEMBER FUNCTIONS
	auto send_request() -> rclcpp::Client<custom_interfaces::srv::SensorRead>::SharedResponse
		// make Request object
		// wait for service
		// send request
		// Simulate synchronous callback: wait_for future.
		// return SharedResponse

```


```c++
class SensorReadPublisher : public rclcpp::Node // Wrapper for TimerPublisher
SensorReadPublisher(std::shared_ptr<SensorClient> sensor1_client,  
                    std::shared_ptr<SensorClient> sensor2_client,  
                    int sensor1_num_samples,  
                    int sensor2_num_samples)
    //Constructor: call base Node with name "sensor_read_publisher". 
    //Initialize my member variables
    // use create_wall_timer to create my timer_
    - MEMBER ATTRIBUTES
    std::shared_ptr<SensorClient> sensor1_client;  
    std::shared_ptr<SensorClient> sensor2_client;  
    rclcpp::Publisher<custom_interfaces::msg::SensorReadCombined>::SharedPtr publisher_;  
    int sensor1_num_samples;  
    int sensor2_num_samples;  
    rclcpp::CallbackGroup::SharedPtr callback_group;  
    rclcpp::TimerBase::SharedPtr timer_; // wall timer: Publishes every 2ms.
    - MEMBER FUNCTIONS
    void timer_callback()
	    // Send a request for data from both sensors via my clients for each of them
	    // Generate combined message publishing, filling in data from both Client Responses.
	    // Publish the combined message to my topic.
```


```c++
class SensorReadSubscriber : public rclcpp::Node // Subscriber to the topic we Publish to
	#define MAX_NUM_DATAPOINTS 100 // Maximum number of datapoints we can receive in a SensorReadCombined.
	SensorReadSubscriber()  
        : Node("sensor_read_subscriber") 
	    // Constructor: Call base Node with name "sensor_read_subscriber".
		// Create subscription 
	void topic_callback(const custom_interfaces::msg::SensorReadCombined & msg) const 
		// Callback: Prints received messages to console using help of print_sensor_sample
	template<int N> // N = Maximum length of samples. 
	void print_sensor_sample(const rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample, N>* sensor_data,  
                         int num_datapoints) const
        // Helper function for printing datapoints to console. Template: Uses N, the Maximum number of datapoints we can receive in a SensorReadCombined to initialize sensor_data type (BoundedVector) correctly.
bringup_py.py & bringup_cpp.cpp: See Overview of Control Flow.
```
# Notes on Number of Samples to Request from Sensor
- This is a very interesting problem in of its own. I will include some analysis on the problem when we do not consider the latency of ROS or of the code itself; however, through timed tests, models for latency in ROS and the code can be incorporated into this analysis.
## Problem Formulation
- Sensor1 samples every 0.5ms with overhead 1ms, uncertain latency uniform between 0-1ms.
- Sensor2 samples every 0.25ms with overhead 3ms, uncertain latency uniform between 0-1ms.
- Must publish every 2ms.
- Question: Given we are at a certain timepoint `t` in the cycle, possibly with some samples already from sensor1 and sensor2, how many more samples `N` do we query from the SensorService?
	- This formulation includes the possibility of dynamically choosing different number of samples to query based on: 
		- where we are in the cycle
		- how many samples we already have
## Analysis of Problem:
### Sensible Choices
- With an uncertainty range of 0-1ms for the overhead delay, half of all choices do not make sense. 
	- For example, if we are at `t=0` in the cycle, for sensor1:
		- querying 1 sample is expected to take between 1.5-2.5ms. So, we have a 50% chance of publishing in the current cycle, and 50% chance of publishing in the subsequent cycle. 
		- If we query 2 samples, the expected time is between 2-3ms. We have a 100% chance of publishing in the subsequent cycle, so we might as well query for 4 samples, having an expected time between 3-4ms, and we still will 100% publish in the subsequent cycle but will have twice as much data.
	- Following this logic, at `t=0`, for sensor1 only `N`=1, 4, 5, 8, 9... samples make sense, and for sensor2 only 1,2,3,8,9,...make sense. At other values of `t`, a different set of half of all possibilities make sense.
### An Answer for Static Choices Considering the Tradeoff: Late Data vs. More Data
- The more samples we query, the more data we get with the same static overhead, but our data also arrives later. 
- By static choice, I mean that the num_samples is fixed.
- For sensor2, even with 1 sample, we are already expected to take 3.25-4.25ms, so we will either be 1 or 2 cycles late. We can sample 8 and still be guaranteed to be only 2 cycles late (expected time 5-6ms). So, I propose to choose `N`=8 samples to take advantage of the high overhead.
- For sensor1, given that we are guaranteed to be 2 cycles late with querying 8 samples, I propose `N`=1 sample so that we have some chance of publishing within the current cycle. Otherwise, we might as well only publish at 250Hz!
- This is the solution implemented in the code.
### What about Dynamic Choices? How to Model the Tradeoff?
- If we can dynamically choose how many samples to take, we have to consider the Late Data vs. More Data tradeoff.
- I propose a framework to model the expected value of different decisions. 
#### Value of Additional Samples
- We can use an information-theoretic perspective to model this: How much does each additional sensor sample decrease the uncertainty of the true value it is measuring?
	- We can model the noise of the sensor based on data adapted to a pre-defined model (i.e. Gaussian). Based on the noise of the sensor, the information we receive changes: 
		- with a noisy sensor, we will not gain as much information and need more samples to reduce uncertainty enough.
		- With an accurate sensor, fewer samples may suffice and additional samples may not provide much decrease in uncertainty.
#### Decrease of Information Over Time
- We need a discount to represent how data becomes less valuable over time. For example we could do an exponential decrease: Compared to data from the same cycle, data 1 cycles late has half the value, data 2 cycles late has a quarter the value, 3 cycles late := an eighth of the value, etc.
#### Modeling the Expected Value of Different Decisions
- Now, we need to ask: For each number of queries `N`, what is the expected value of that decision? We need to calculate the probability of data arriving in different subsequent cycles `C`, and multiply that probability with the Value produced by having `N` samples in cycle `C` using the models described above. 
- We can calculate the expected values of different decisions, and choose the one with the maximum expected value.
# Git Notes
- Initial development was on master. Then, as I started using CLion on my mac more, a push was required every time I wanted to run updated code on VirtualBox. 
- Therefore, I switched to a Feature Branch workflow, creating feature branches.
- Once a feature is finished, I:
	- made a copy branch
	- rebased the copy on master, squashing most commits to leave a few high-level updates.
	- merge master to copy (fast-forward)
- Therefore, original feature branches with all commits are also maintained for full version history and have been pushed.
# Future Work
If I had more time, I would suggest the following improvements to my code:
- I used one executor for CPP and one for Python. Perhaps realistically these would be on different computers, but executors induce significant overhead, so ideally I could avoid it on the same device. Perhaps I can use a Python Launch file, make an executor there, and pass that executor to both my Python and CPP bringup files.
- Multithread Lock for editing the data reservoir: prevent query thread from modifying at the same time as the service callback.
- Improve messaging: Maybe we can send addl info with sensor
- remember to reduce buffer size! Will be pretty small...actually has to be capped at 8 samples for sensor2 and 2 samples for sensor1.i.e. which sensor wrote this, timestamps by period, etc.
- shutdown cleanly: I believe I should be able to `Ctrl + C` instead of `Ctrl + \`, so I would like to make sure I am shutting nodes down correctly.
- Launch file: a single XML/YAML launch file for all nodes.
- Additional Testing:
	- Valgrind: Memory checks.
	- Automate many (100+) runs to catch intermittent bugs.
- Timing & Latency Analysis: Check where bottlenecks are and improve.
- Incorporate Timing Analysis into Decision about How Many Samples `N` to Query
## Maintainer / Contact
Varun Kamat, please reach me at: varunkamat23@gmail.com for any questions. 
