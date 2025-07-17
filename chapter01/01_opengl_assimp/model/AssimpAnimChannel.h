#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <assimp/anim.h>

// 描述了某一根骨骼（或节点）在一个动画片段中的所有关键帧数据。
// 播放时通过插值获得任意时刻的变换。
class AssimpAnimChannel {
  public:
    void loadChannelData(aiNodeAnim* nodeAnim);
    std::string getTargetNodeName();
    float getMaxTime();

    glm::mat4 getTRSMatrix(float time);

    glm::vec3 getTranslation(float time);
    glm::vec3 getScaling(float time);
    glm::quat getRotation(float time);

  private:
    std::string mNodeName;

    /* use separate timinigs vectors, just in case not all keys have the same time */
    std::vector<float> mTranslationTiminngs{};
    std::vector<float> mInverseTranslationTimeDiffs{};
    std::vector<float> mRotationTiminigs{};
    std::vector<float> mInverseRotationTimeDiffs{};
    std::vector<float> mScaleTimings{};
    std::vector<float> mInverseScaleTimeDiffs{};

    /* every entry here has the same index as the timing for that key type */
    std::vector<glm::vec3> mTranslations{};
    std::vector<glm::vec3> mScalings{};
    std::vector<glm::quat> mRotations{};

    // Constant	超出区间时，值保持第一个/最后一个关键帧的值
    // Repeat/Loop	超出区间时，动画时间回绕到区间内（循环播放）
    // Mirror	超出区间时，动画时间回绕并反向（来回播放）
    // Linear	超出区间时，按最后两个关键帧的趋势线性外推
    // 决定动画在“起始关键帧之前”如何表现。
    unsigned int mPreState = 0;
    // 决定动画在“结束关键帧之后”如何表现。
    unsigned int mPostState = 0;
};
