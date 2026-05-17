#pragma once

#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager() {}
	~EnemyManager() {}

	// 初期化（ファイルから設計図を読み込む）
	void LoadTimeline(const std::string& filePath);

	// 毎フレームの更新（敵の生成チェック）
	void Update(std::vector<std::shared_ptr<BaseObject>>& objList);

	void AddTime(int frame);

private:
	struct SpawnData {
		int frame;              // 出現時間
		Enemy::Type type;       // 敵の種類
		Math::Vector3 pos;      // 出現座標
	};

	std::vector<SpawnData> m_timeline; // 設計図リスト
	int m_timelineIndex = 0;           // 現在の進行位置
	int m_elapsedFrame = 0;            // 経過フレーム
};