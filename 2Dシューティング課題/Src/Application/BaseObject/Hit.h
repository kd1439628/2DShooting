#pragma once
#include "Explosion/Explosion.h"

class BaseObject;

class Hit
{
public:

	// 全オブジェクトのリストを受け取り、当たり判定を一括実行する
	void AllCollision(std::vector<std::shared_ptr<BaseObject>>& objList);

	// 合計スコアを外から取得できるようにする
	int GetScore() const { return m_totalScore; }

private:
	// 個別の判定ロジック
	void CheckCollision(std::shared_ptr<BaseObject> objA, std::shared_ptr<BaseObject> objB, std::vector<std::shared_ptr<BaseObject>>& objList);


	int m_totalScore = 0;
	int m_lastHealScore = 0; //最後に回復した時のスコアを記録
};