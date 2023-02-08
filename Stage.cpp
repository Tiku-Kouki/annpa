#include"Stage.h"


Stage::Stage() {

	 blockSize = 128;//�u���b�N�T�C�Y

	//�X�N���[������
	 scrollStartX = 400;
	 lineY = 0;

	 scrollX = 0;

	 monitorX = 0;

	 resources = new Resources;
	
	 StageSelect = 0;
}




void Stage::Draw() {
	

		//�u���b�N�̕`��

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 30; x++) {
			if (StageSelect == 0) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(
					x * 128 - scrollX, y * 128, resources->gh1, 1, 1, 0.0f, WHITE);
			}
			if (map[y][x] == 2) {
				monitorX = x * 128 - scrollX;
				Novice::DrawSprite(
					monitorX, y * 128, resources->gh1, 1, 1, 0.0f, RED);
			}
			if (map[y][x] == 3) {
				monitorX = x * 128 - scrollX;
				Novice::DrawSprite(
					monitorX, y * 128, resources->gh1, 1, 1, 0.0f, BLUE);
			}
		
			}
			if (StageSelect == 1) {
				if (map1[y][x] == 1) {
					Novice::DrawSprite(
						x * 128 - scrollX, y * 128, resources->gh1, 1, 1, 0.0f, WHITE);
				}
				if (map1[y][x] == 2) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh1, 1, 1, 0.0f, RED);
				}
				if (map1[y][x] == 3) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh1, 1, 1, 0.0f, BLUE);
				}

			}if (StageSelect == 2) {
				if (map2[y][x] == 1) {
					Novice::DrawSprite(
						x * 128 - scrollX, y * 128, resources->gh1, 1, 1, 0.0f, WHITE);
				}
				if (map2[y][x] == 2) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh1, 1, 1, 0.0f, RED);
				}
				if (map2[y][x] == 3) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh1, 1, 1, 0.0f, BLUE);
				}
				if (map2[y][x] == 4) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh1, 1, 1, 0.0f, GREEN);
				}
				if (map2[y][x] == 5) {
					monitorX = x * 128 - scrollX;
					Novice::DrawSprite(
						monitorX, y * 128, resources->gh1, 1, 1, 0.0f, GREEN);
				}

			}
		}
		
	}
	
	
}

void Stage::Reset()
{
	for (int x = 0; x < mapHeight; x++) {

		for (int y = 0; y < mapWidth; y++){
		//�`���[�g���A��


			
				map[x][y] = mapR[x][y];


			
				//�X�e�[�W�P
				map1[x][y] = map1R[x][y];

			
				//�X�e�[�W2
				map2[x][y] = map2R[x][y];

				
		}

	}


	

	
}

