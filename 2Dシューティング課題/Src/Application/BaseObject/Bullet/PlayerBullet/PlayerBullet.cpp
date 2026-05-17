#include "PlayerBullet.h"
#include "../../Enemies/Enemy.h"

void PlayerBullet::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	// 1. 索敵範囲
	float searchRadius = 150.0f;
	float closestDistSq = searchRadius * searchRadius;
	std::shared_ptr<Enemy> target = nullptr;

	// 2. リストの中から一番近い敵を探す
	for (auto& obj : objList)
	{
		auto enemy = std::dynamic_pointer_cast<Enemy>(obj);

		// 敵が存在して、かつ生きている場合のみ判定する
		if (enemy && enemy->IsAlive())
		{
			// 弾と敵の距離の2乗を計算
			float distSq = (enemy->GetPos() - m_pos).LengthSquared();

			// 索敵範囲内で、より近い敵がいたらターゲットを更新
			if (distSq < closestDistSq)
			{
				closestDistSq = distSq;
				target = enemy;
			}
		}
	}

	// 3. ターゲットが見つかったら、その方向へ少しずつ向きを変える
	if (target)
	{
		// 敵の方向へのベクトルを計算
		Math::Vector3 dir = target->GetPos() - m_pos;
		dir.Normalize(); // 長さを1にする

		// 現在の進行方向（m_move）に、敵の方向（dir）を少しだけ足して曲げる
		// ここの数値を大きくするとホーミングが強くなり、小さくすると弱くなる
		m_move += dir * 0.8f;

		// 弾のスピードを一定（12.0f）に保つ
		m_move.Normalize();
		m_move *= 12.0f;
	}

	// 4. 親クラス（Bullet）のUpdateを呼んで、実際の移動と画面外削除を行う
	Bullet::Update(objList);
}

void PlayerBullet::Init()
{
	m_tex.Load("Textures/Bullet1.png"); // 自機弾のパス
	m_aliveFlg = true;
}
