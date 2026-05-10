#include "Hit.h"
#include "BaseObject.h"
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Bullet/EnemyBullet/EnemyBullet.h"
#include "Bullet/PlayerBullet/PlayerBullet.h"
#include "UI/UI.h"


void Hit::AllCollision(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	// 総当たり判定
	for (int i = 0; i < objList.size(); ++i)
	{
		for (int j = i + 1; j < objList.size(); ++j)
		{
			auto& objA = objList[i];
			auto& objB = objList[j];

			// どちらかが死んでいたらスキップ
			if (!objA->IsAlive() || !objB->IsAlive()) continue;

			// 距離判定
			float distSq = (objA->GetPos() - objB->GetPos()).LengthSquared();
			float radiusSum = objA->GetRadius() + objB->GetRadius();

			if (distSq <= (radiusSum * radiusSum))
			{
				CheckCollision(objA, objB, objList);
			}
		}
	}
}

void Hit::CheckCollision(std::shared_ptr<BaseObject> objA, std::shared_ptr<BaseObject> objB, std::vector<std::shared_ptr<BaseObject>>& objList)
{
	// --- 1. プレイヤーの弾 vs 敵 ---
	auto pBullet = std::dynamic_pointer_cast<PlayerBullet>(objA);
	auto enemy = std::dynamic_pointer_cast<Enemy>(objB);
	if (!pBullet)
	{ // 逆の組み合わせもチェック
		pBullet = std::dynamic_pointer_cast<PlayerBullet>(objB);
		enemy = std::dynamic_pointer_cast<Enemy>(objA);
	}
	if (pBullet && enemy)
	{
		if (pBullet->GetPos().x > 656.0f)
		{
			return;
		}
		enemy->OnDamage(1);   // 敵にダメージ
		pBullet->OnCollision(); // 弾を消す（OnCollisionはBaseObjectに定義）
		// 敵を倒した時のスコア・回復処理
		if (!enemy->IsAlive())
		{
			int scorePoint = 0;
			// 敵の種類を判別（EnemyにGetTypeが必要）
			auto type = enemy->GetType();
			if (type == Enemy::Type::Normal)   scorePoint = 100;
			else if (type == Enemy::Type::Hard)     scorePoint = 200;
			else if (type == Enemy::Type::Assault)  scorePoint = 500;

			m_totalScore += scorePoint;


		}
		return;
	}

	// --- 2. 敵の弾 vs プレイヤー ---
	auto eBullet = std::dynamic_pointer_cast<EnemyBullet>(objA);
	auto player = std::dynamic_pointer_cast<Player>(objB);
	if (!eBullet) {
		eBullet = std::dynamic_pointer_cast<EnemyBullet>(objB);
		player = std::dynamic_pointer_cast<Player>(objA);
	}
	if (eBullet && player) {
		player->OnDamage(1); // プレイヤー死亡など
		eBullet->OnCollision(); // 弾消滅
		return;
	}

	// --- 3. 敵（Assaultなど） vs プレイヤー ---
	auto enemyBody = std::dynamic_pointer_cast<Enemy>(objA);
	auto playerBody = std::dynamic_pointer_cast<Player>(objB);
	if (!enemyBody) {
		enemyBody = std::dynamic_pointer_cast<Enemy>(objB);
		playerBody = std::dynamic_pointer_cast<Player>(objA);
	}
	if (enemyBody && playerBody) {
		playerBody->OnDamage(99);
		enemyBody->OnDamage(99); // 体当たりは自分も大ダメージ
		return;
	}
}
