#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;
layout (location = 4) in uvec4 aBoneNum; // 骨骼编号
layout (location = 5) in vec4 aBoneWeight; // 骨骼权重

layout (location = 0) out vec4 color;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec2 texCoord;

layout (std140) uniform Matrices {
  mat4 view;
  mat4 projection;
};

layout (std140) uniform BoneMatrices {
  mat4 boneMat[256];
};

uniform int aModelStride;

void main() {

  // 蒙皮，将骨骼的变换应用到网格上的顶点
  mat4 skinMat =
    aBoneWeight.x * boneMat[aBoneNum.x + gl_InstanceID * aModelStride] +
    aBoneWeight.y * boneMat[aBoneNum.y + gl_InstanceID * aModelStride] +
    aBoneWeight.z * boneMat[aBoneNum.z + gl_InstanceID * aModelStride] +
    aBoneWeight.w * boneMat[aBoneNum.w + gl_InstanceID * aModelStride];

  gl_Position = projection * view * skinMat * vec4(aPos, 1.0);
  color = aColor;
  normal = vec3(transpose(inverse(skinMat)) * vec4(aNormal, 1.0));
  texCoord = aTexCoord;
}
