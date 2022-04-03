#include <functional>
#include <rclcpp/rclcpp.hpp>
#include <thread>

#include "RRTStar.hpp"
#include "obstacleData.hpp"
#include "visualize.hpp"
ObstacleData obstacleData("./src/calc_route/ABU2019Field.csv");
std::vector<PointNode> pointTree;
RRTStar rrtstar;

RouteVisualize::SharedPtr visualizer;
using namespace std::chrono_literals;
class calcRoute : public rclcpp::Node {
  public:
	calcRoute() : Node("calc_route") {
		timer_ = this->create_wall_timer(1ns, std::bind(&calcRoute::timer_callback, this));
	}

  private:
	void timer_callback() {
	}
	rclcpp::TimerBase::SharedPtr timer_;
};
void calc() {
	while (1) rrtstar.calc();
}
int main(int argc, char* argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::executors::SingleThreadedExecutor exec;
	auto node1 = std::make_shared<calcRoute>();
	auto node2 = visualizer = std::make_shared<RouteVisualize>();

	std::thread(calc).detach();

	exec.add_node(node1);
	exec.add_node(node2);
	exec.spin();
	rclcpp::shutdown();
	return 0;
}