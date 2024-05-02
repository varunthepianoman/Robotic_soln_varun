# [Coding Complete. Full Documentation Expected by 5/2/24 @ 3pm] Robotic_HW Solution

[Coding Complete. Full Documentation Expected by 5/2/24 @ 3pm]: ReadMe Documentation (including explanation and mathematical framework for how to select number of samples to query) Expected by Thursday 5/2/24 @ 3pm. I do have Fully Functional Code here, with extensive inline documentation. 

## Maintainer / Contact
Varun Kamat, please reach me at: varunkamat23@gmail.com for any questions.

## Relevant Files:
Please note that all code is in src/sensor_package_cpp and src/custom_interfaces folder.

### ROS2 Nodes
Launch Node for Python Scripts: src/sensor_package_cpp/sensor_package_cpp/bringup_py.py
Sensor: src/sensor_package_cpp/sensor_package_cpp/submodules/sensor.py
Service for Sensor: src/sensor_package_cpp/sensor_package_cpp/submodules/sensor_service.py
Launch Node for C++ Scripts src/sensor_package_cpp/src/bringup_cpp.cpp
Sensor Client: src/sensor_package_cpp/include/sensor_package_cpp/sensor_client.hpp
Sensor Publisher: src/sensor_package_cpp/include/sensor_package_cpp/sensor_read_publisher.hpp
Sensor Subscriber: src/sensor_package_cpp/include/sensor_package_cpp/sensor_subscriber.hpp

### Custom Interface
Single Sensor Single Sample Message: src/custom_interfaces/msg/SensorSample.msg
Single Sensor Many Samples Service: src/custom_interfaces/srv/SensorRead.srv
Both Sensor SamplesMessage to Publish: src/custom_interfaces/msg/SensorReadCombined.msg

### Note
There may be other files here, including the all-python prototype package sensor_package, but the above files are the relevant ones for the final solution.

## Context
The design of our cells in Machina Labs has evolved over the past years. Currently, each of our cells has two articulated industrial robots on rails (a total of 7 axes) and a frame with hydraulic clamps. For the parts to form correctly, we must exert and maintain a dynamic force during the forming in a very accurate location in space. Currently, each robot is equipped with a load cell. See a quick video about our process [here](https://www.youtube.com/watch?v=iqYMprTEXRI). We are using ROS2 to collect the data from the network and control the robots in real-time. As a robotic engineer, we keep developing different modules for our network to add features to the system.  
 
## Objective
The goal of This project is to build a ROS2 network that collects data from 3-DOF sensors and makes the filtered data available as a ROS service and topic. Since we cannot send a real sensor to all of our applicants, we made a simple simulator (sensor.py) that mimics the behavior of a real sensor but with random data. 
- The first task is to make a custom service for 3-DOF sensor 
- The second task is to make a ROS2 service server that continuously reads data from the sensor and has the latest filter data available for the client service that you make. 
- Finally, please make a simple client that calls two of these services and publishes them to a topic at 500Hz. Please keep in mind that your service servers can run slower than 500Hz. 
- You can define a second server in the simulator to modify the code and run two at the same time.
- You can check the example.py to see how to make calls to the sensor

## Grading Criteria
- We’re looking for code that is clean, readable, performant, and maintainable.
- The developer must think through the process of deploying and using the solution and provide the necessary documentation. 
- The sensor samples with 2000Hz, and you can request a specific number of samples in each call. Each call also has a ~1ms delay on top of the sampling time. We would like to hear your thought on picking the number of samples that you read in each call. 

## Submission
To submit the assignment, do the following:

1. Navigate to GitHub's project import page: [https://github.com/new/import](https://github.com/new/import)

2. In the box titled "Your old repository's clone URL", paste the homework repository's link: [https://github.com/Machina-Labs/robotic_hw](https://github.com/Machina-Labs/robotic_hw)

3. In the box titled "Repository Name", add a name for your local homework (ex. `Robotic_soln`)

4. Set the privacy level to "Public", then click "Begin Import" button at bottom of the page.

5. Develop your homework solution in the cloned repository and push it to GitHub when you're done. Extra points for good Git hygiene.

6. Send us the link to your repository.

## ROS2
Install instructions (Ubuntu): [https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debians.html)

ROS2 tutorials: [https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries.html](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries.html)

