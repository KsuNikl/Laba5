import os
from dataclasses import dataclass

@dataclass
class Cell:
    product: str = ""
    count: int = 0

class Warehouse:
    def init(self):
        self.cells = {}
        self.init_cells()
        self.load_cells()
    
    def init_cells(self):
        """Инициализация всех ячеек по ТЗ"""
        for zone in ['A', 'B', 'C']:
            for stell in range(1, 15):
                for vert in range(1, 7):
                    for polka in range(1, 21):
                        address = f"{zone}{stell:02d}{vert}{polka:02d}"
                        self.cells[address] = Cell()
    
    def load_cells(self):
        """Загрузка данных из файла"""
        if os.path.exists("cells.txt"):
            with open("cells.txt", "r") as f:
                for line in f:
                    parts = line.strip().split()
                    if len(parts) == 3:
                        address, product, count = parts
                        self.cells[address] = Cell(product, int(count))
    
    def save_cells(self):
        """Сохранение данных в файл"""
        with open("cells.txt", "w") as f:
            for address, cell in self.cells.items():
                if cell.count > 0:
                    f.write(f"{address} {cell.product} {cell.count}\n")
    
    def add_product(self, product: str, count: int, address: str) -> str:
        """Добавление товара в ячейку"""
        if address not in self.cells:
            return "Такого адреса не существует!"
        
        cell = self.cells[address]
        
        if cell.product and cell.product != product:
            return "Ячейка занята другим товаром!"
        elif count <= 0:
            return "Количество должно быть больше 0!"
        elif count > (10 - cell.count):
            return "Недостаточно места!"
        
        cell.product = product
        cell.count += count
        return "Успешно!"
    
    def remove_product(self, product: str, count: int, address: str) -> str:
        """Удаление товара из ячейки"""
        if address not in self.cells:
            return "Такого адреса не существует!"
        
        cell = self.cells[address]
        
        if not cell.product:
            return "Ячейка пуста!"
        elif cell.product != product:
            return "В ячейке находится другой товар!"
        elif count <= 0:
            return "Количество должно быть больше 0!"
        elif count > cell.count:
            return "Недостаточно товара для удаления!"
        
        cell.count -= count
        if cell.count == 0:
            cell.product = ""
        return "Успешно!"
    
    def get_info(self):
        """Получение информации о складе"""
        product_count = sum(cell.count for cell in self.cells.values())
        total_capacity = len(self.cells) * 10
        
        print(f"\nСклад загружен на {product_count * 100 / total_capacity:.0f}% "
              f"({product_count}/{total_capacity})")
        
        # Занятые ячейки
        print("\nЗанятые ячейки:")
        for address, cell in self.cells.items():
            if cell.count > 0:
                print(f"{address}: {cell.product} {cell.count} шт.")
        
        # Пустые ячейки
        empty = [addr for addr, cell in self.cells.items() if cell.count == 0]
        print("\nПустые ячейки:")
        for i, addr in enumerate(empty, 1):
            print(addr, end=' ')
            if i % 20 == 0:
                print()
        print()
def main():
    warehouse = Warehouse()
    
    print("СКЛАД\n\n"
          "Добавить товар - ADD\n"
          "Удалить товар - REMOVE\n"
          "Информация - INFO\n"
          "Выход - EXIT")
    
    while True:
        try:
            cmd = input("\n    Введите команду > ").strip().upper()
            
            if cmd == "ADD":
                parts = input("Введите <товар> <кол-во> <адрес>: ").strip().split()
                if len(parts) == 3:
                    product, count, address = parts
                    try:
                        count = int(count)
                        print(warehouse.add_product(product, count, address))
                    except ValueError:
                        print("Количество должно быть числом!")
                else:
                    print("Неверный формат команды! Нужно: <товар> <кол-во> <адрес>")
            
            elif cmd == "REMOVE":
                parts = input("Введите <товар> <кол-во> <адрес>: ").strip().split()
                if len(parts) == 3:
                    product, count, address = parts
                    try:
                        count = int(count)
                        print(warehouse.remove_product(product, count, address))
                    except ValueError:
                        print("Количество должно быть числом!")
                else:
                    print("Неверный формат команды! Нужно: <товар> <кол-во> <адрес>")
            
            elif cmd == "INFO":
                warehouse.get_info()
            
            elif cmd == "EXIT":
                warehouse.save_cells()
                print("Данные сохранены. Выход из программы.")
                break
            
            else:
                print("Введена неверная команда!\nПопробуйте снова!")
        
        except KeyboardInterrupt:
            warehouse.save_cells()
            print("\nДанные сохранены. Выход из программы.")
            break
        except Exception as e:
            print(f"Произошла ошибка: {e}")

if name == "main":
    main()
import os
from dataclasses import dataclass

@dataclass
class Cell:
    product: str = ""
    count: int = 0

class Warehouse:
    def init(self):
        self.cells = {}
        self._init_cells()
        self.load_cells()
    
    def _init_cells(self):
        """Инициализация всех ячеек по ТЗ"""
        for zone in ['A', 'B', 'C']:
            for rack in range(1, 15):  # 14 стеллажей
                for section in range(1, 7):  # 6 вертикальных секций
                    for shelf in range(1, 21):  # 20 полок
                        address = f"{zone}{rack:02d}{section}{shelf:02d}"
                        self.cells[address] = Cell()
    
    def load_cells(self):
        """Загрузка данных из файла"""
        if os.path.exists("cells.txt"):
            with open("cells.txt", "r") as f:
                for line in f:
                    parts = line.strip().split()
                    if len(parts) == 3:
                        address, product, count = parts
                        self.cells[address] = Cell(product, int(count))
    
    def save_cells(self):
        """Сохранение данных в файл"""
        with open("cells.txt", "w") as f:
            for address, cell in self.cells.items():
                if cell.count > 0:
                    f.write(f"{address} {cell.product} {cell.count}\n")
    
    def add_product(self, product: str, count: int, address: str) -> str:
        """Добавление товара в ячейку"""
        if address not in self.cells:
            return "Ошибка: адрес не существует"
        
        cell = self.cells[address]
        
        if cell.product and cell.product != product:
            return f"Ошибка: ячейка занята товаром '{cell.product}'"
        if count <= 0:
            return "Ошибка: количество должно быть положительным"
        if cell.count + count > 10:
            return f"Ошибка: превышена вместимость (осталось {10 - cell.count} мест)"
        
        cell.product = product
        cell.count += count
        return f"Добавлено {count} ед. '{product}' в {address}"
    
    def remove_product(self, product: str, count: int, address: str) -> str:
        """Удаление товара из ячейки"""
        if address not in self.cells:
            return "Ошибка: адрес не существует"
        
        cell = self.cells[address]
        
        if not cell.product:
            return "Ошибка: ячейка пуста"
        if cell.product != product:
            return f"Ошибка: в ячейке находится '{cell.product}'"
        if count <= 0:
            return "Ошибка: количество должно быть положительным"
        if count > cell.count:
            return f"Ошибка: недостаточно товара (доступно {cell.count})"
        
        cell.count -= count
        if cell.count == 0:
            cell.product = ""
        return f"Удалено {count} ед. '{product}' из {address}"
    
    def get_warehouse_stats(self):
        """Статистика по складу"""
        used = sum(cell.count for cell in self.cells.values())
        total = len(self.cells) * 10
        return {
            'total_cells': len(self.cells),
            'used_cells': sum(1 for cell in self.cells.values() if cell.count > 0),
            'empty_cells': sum(1 for cell in self.cells.values() if cell.count == 0),
            'total_products': used,
            'usage_percent': round(used * 100 / total, 1)
        }
    
    def get_zone_stats(self, zone: str):
        """Статистика по зоне"""
        zone_cells = {addr: cell for addr, cell in self.cells.items() if addr.startswith(zone)}
        used = sum(cell.count for cell in zone_cells.values())
        total = len(zone_cells) * 10
        return {
            'zone': zone,
            'total_cells': len(zone_cells),
            'used_cells': sum(1 for cell in zone_cells.values() if cell.count > 0),
            'total_products': used,
            'usage_percent': round(used * 100 / total, 1) if total > 0 else 0
        }
    
    def get_occupied_cells(self):
        """Список занятых ячеек"""
        return {
            addr: {'product': cell.product, 'count': cell.count}
for addr, cell in self.cells.items()
            if cell.count > 0
        }
    
    def get_empty_cells(self):
        """Список пустых ячеек"""
        return [addr for addr, cell in self.cells.items() if cell.count == 0]