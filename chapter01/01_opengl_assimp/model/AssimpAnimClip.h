#pragma once

#include <string>
#include <vector>
#include <memory>

#include <assimp/anim.h>

#include "AssimpAnimChannel.h"

// 描述一个完整的动画动作，比如“走路”、“跳跃”、“攻击”。包含了所有骨骼在该动作下的动画数据
// 可以同时播放多个AnimClip，对同一骨骼的AnimChannel做加权混合，实现平滑过渡。
class AssimpAnimClip {
  public:
    void addChannels(aiAnimation* animation);
    std::vector<std::shared_ptr<AssimpAnimChannel>> getChannels();

    std::string getClipName();
    float getClipDuration();
    float getClipTicksPerSecond();

    void setClipName(std::string name);

  private:
    std::string mClipName;
    double mClipDuration = 0.0f;
    double mClipTicksPerSecond = 0.0f;

    std::vector<std::shared_ptr<AssimpAnimChannel>> mAnimChannels{};
};
