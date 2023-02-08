#include"Stage.h"


Stage::Stage() {

	 blockSize = 128;//ブロックサイズ

	//スクロール処理
	 scrollStartX = 400;
	 lineY = 0;

	 scrollX = 0;

	 monitorX = 0;

	 resources = new Resources;
	
	 StageSelect = 0;
}




void Stage::Draw() {
	//ブロックの描画
	Novice::DrawSprite(0, 0, resources->bg1, 1, 1, 0.0f, WHITE);
	

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 30; x++) {
			
			if (map[y][x] == 1) {
				Novice::DrawSprite(
					x * 128 - scrollX, y * 128, resources->gh1, 1, 1, 0.0f, WHITE);
			}
			if (map[y][x] == 2) {
				monitorX = x * 128 - scrollX;
				Novice::DrawSprite(
					monitorX, y * 128, resources->blod, 1, 1, 0.0f, WHITE);
			}
			if (map[y][x] == 3) {
				monitorX = x * 128 - scrollX;
				Novice::DrawSprite(
					monitorX, y * 128, resources->gh2, 1, 1, 0.0f, WHITE);
			}
		
			
			
				
		}
		
	}
	
	
}

void Stage::Draw1()
{
	Novice::DrawSprite(0, 0, resources->bg2, 1, 1, 0.0f, WHITE);
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 30; x++) {
			
			
				if (map1[y][x] == 1) {
					Novice::DrawSprite(
						x * 128 - scrollX, y * 128, resources->gh1, 1, 1, 0.0f, WHITE);
				}
				if (map1[y][x] == 2) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->blod, 1, 1, 0.0f, WHITE);
				}
				if (map1[y][x] == 3) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh2, 1, 1, 0.0f, WHITE);
				}

			
		}

	}
}

void Stage::Draw2()
{
	Novice::DrawSprite(0, 0, resources->bg3, 1, 1, 0.0f, WHITE);
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 30; x++) {
			
				if (map2[y][x] == 1) {
					Novice::DrawSprite(
						x * 128 - scrollX, y * 128, resources->gh1, 1, 1, 0.0f, WHITE);
				}
				if (map2[y][x] == 2) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->blod, 1, 1, 0.0f, WHITE);
				}
				if (map2[y][x] == 3) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh2, 1, 1, 0.0f, WHITE);
				}
				if (map2[y][x] == 4) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->needU, 1, 1, 0.0f, WHITE);
				}
				if (map2[y][x] == 5) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->needD, 1, 1, 0.0f, WHITE);
				}

			
		}

	}
}



void Stage::Reset()
{
	for (int x = 0; x < mapHeight; x++) {

		for (int y = 0; y < mapWidth; y++){
		//チュートリアル


			
				map[x][y] = mapR[x][y];


			
				//ステージ１
				map1[x][y] = map1R[x][y];

			
				//ステージ2
				map2[x][y] = map2R[x][y];

				
		}

	}


	

	
}

