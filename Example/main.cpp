#include "prototype_robot.h"
#include <chrono>
#include "interface_can.hpp"
#include "fakekr.cpp"

PrototypeRobot robot(&hcan1);
#define SPEED 4000

CAN_context *canCtx = get_can_ctx(&hcan1);

inline float MaxAngleDifference(const int32_t *angles1, const int32_t *angles2)
{
  float max_diff = 0.0;
  for (uint8_t i = 0; i < 7; i++)
  {
    float diff = std::abs(static_cast<float>(angles1[i] - angles2[i]));
    if (diff > max_diff)
    {
      max_diff = diff;
    }
  }
  return max_diff;
}

/* Default Entry -------------------------------------------------------*/
int main(void)
{
  // Init all communication
  CAN_TypeDefHD();

  // Init Robot.
  robot.Init();

  // Init kinematic
  fakeKR kr;
  std::vector<int32_t> jointData[7];
  kr.init_fakeKR("../Robot/algorithms/kinematic/data2.txt", jointData);

  // Start measuring time
  auto start = std::chrono::high_resolution_clock::now();

  int32_t angles1[7] = {0};

  // move to zero position
  robot.MoveJoints(angles1);
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  size_t maxLength = 0;
  for (int i = 0; i < 7; ++i)
  {
    if (jointData[i].size() > maxLength)
    {
      maxLength = jointData[i].size();
    }
  }
  int32_t angles2[7] = {0};
  float maxIntervale = 0;
  int time;
  for (size_t i = 0; i < maxLength; ++i)
  {
    for (int j = 0; j < 7; ++j)
    {
      if (i < jointData[j].size())
      {
        angles2[j] = jointData[j][i];
      }
      else
      {
        std::cout << "Joint " << j << " degree N/A ";
      }
    }
    maxIntervale = MaxAngleDifference(angles1, angles2);
    if (maxIntervale > 1)
    {
      robot.MoveJoints(angles2);
      time = (maxIntervale / ((360 * SPEED) / 101 / 101)) * 1000000;

      std::this_thread::sleep_for(std::chrono::microseconds(time));

      for (int i = 0; i < 7; i++)
      {
        angles1[i] = angles2[i];
      }
      std::cout << std::endl;
    }
  }
  int32_t zeropos[7] = {0};
  robot.MoveJoints(zeropos);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  printf("Test Finished\n");
  printf("total message processed: %d\n", canCtx->TxCompleteCallbackCnt);
  printf("total message aborted: %d\n", canCtx->TxAbortCallbackCnt);
  printf("Total time taken: %f\n", duration.count());
  printf("Frame per second: %f\n", canCtx->TxCompleteCallbackCnt / duration.count());

  // printf("xxxxxxxxxxxx");
  // printf("robotid: %u\n", canCtx->node_id);
  return 0;
}
