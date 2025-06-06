regions = {}

def change(region, center):
    if(region in regions):
        #переименование центра
        if (center == regions[region]):
            print(f'Невозможно переименовать {center} в {center}')
        else:
            old_center = regions[region]
            regions[region] = center
            print(f'Region {region} has changed its administrative center from {old_center} to {center}')
    else:
        #создание региона
        regions[region] = center
        print(f'New region {region} with administrative center {center}')

def rename(old_region, new_region):
    if (old_region in regions):
        if (new_region in regions):
            print(f'Регион с названием {new_region} уже существует!')
        else:
            center = regions[old_region]
            regions.pop(old_region)
            regions[new_region] = center
            print(f'{old_region} has been renamed to {new_region}')
    else:
        print(f'Региона с названием {old_region} не существует!')

def about(region):
    if (region in regions):
        print(f'{region} has administrative center {regions[region]}')
    else:
        print(f'Региона с названием {region} не существует!')

def all():
    if len(regions) > 0:
        print("Список регионов:")
        for region, center in regions.items():
            print(f'{region} - {center}')
    else:
        print("Список регионов пуст!")


N = int(input("Введите количество запросов > "))
for i in range(N):
    cmd = input("   Введите команду > ").split()
    if cmd[0] == "CHANGE" and len(cmd) == 3:
        change(cmd[1], cmd[2])
    elif cmd[0] == "RENAME" and len(cmd) == 3:
        rename(cmd[1], cmd[2])
    elif cmd[0] == "ABOUT" and len(cmd) == 2:
        about(cmd[1])
    elif cmd[0] == "ALL" and len(cmd) == 1:
        all()
    else:
        print("Введена неверная команда!")