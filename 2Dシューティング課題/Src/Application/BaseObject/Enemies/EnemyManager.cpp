#include "EnemyManager.h"

void EnemyManager::LoadTimeline(const std::string& filePath)
{
	m_timeline.clear();
	m_timelineIndex = 0;
	m_elapsedFrame = 0;

	FILE* fp;
	if ((fp = fopen(filePath.c_str(), "r")) == nullptr) return;

	int frame, type;
	float x, y;
	// カンマ区切りの数値を読み込む
	while (fscanf(fp, "%d,%d,%f,%f", &frame, &type, &x, &y) == 4)
	{
		SpawnData data;
		data.frame = frame;
		data.type = static_cast<Enemy::Type>(type);
		data.pos = { x, y, 0.0f };
		m_timeline.push_back(data);
	}
	fclose(fp);
}

void EnemyManager::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	m_elapsedFrame++;

	while (m_timelineIndex < m_timeline.size() &&
		m_elapsedFrame >= m_timeline[m_timelineIndex].frame)
	{
		const auto& data = m_timeline[m_timelineIndex];

		auto newEnemy = std::make_shared<Enemy>();
		// Enemyクラスの初期化関数を呼ぶ
		newEnemy->InitializeAs(data.type, data.pos);
		objList.push_back(newEnemy);

		m_timelineIndex++;
	}
}

void EnemyManager::AddTime(int frame)
{
	m_elapsedFrame += frame;
	if (m_elapsedFrame < 0) {
		m_elapsedFrame = 0;
	}

	// タイムラインのインデックス（次にどの敵を出現させるか）を現在の経過時間に合わせて再計算
	m_timelineIndex = 0;
	while (m_timelineIndex < m_timeline.size() &&
		m_timeline[m_timelineIndex].frame <= m_elapsedFrame)
	{
		m_timelineIndex++;
	}
}
