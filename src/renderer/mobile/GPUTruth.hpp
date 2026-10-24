#pragma once

#ifdef BISMUTH_GLES_BACKEND

namespace cocos2d {
class CCSprite;
class CCSpriteBatchNode;
}

class Renderer;
class GJGroundLayer;

namespace GPUTruth {
void beginFrame(Renderer* renderer);
void recordObjectBatch(Renderer* renderer, cocos2d::CCSpriteBatchNode* batch);
void recordObjectFailure(Renderer* renderer);
void recordBackground(Renderer* renderer, bool submitted);
void recordGroundSuccess(Renderer* renderer, GJGroundLayer* ground, cocos2d::CCSprite* sprite);
void recordGroundFailure(Renderer* renderer, GJGroundLayer* ground, cocos2d::CCSprite* sprite);
void finishFrame(Renderer* renderer);
}

#endif
