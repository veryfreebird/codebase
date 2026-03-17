import tkinter as tk
from tkinter import messagebox, ttk
import time
import random

class ChineseChessBoard:
    def __init__(self, root):
        self.root = root
        self.root.title("中国象棋棋盘 - 马步遍历问题")
        self.root.geometry("900x700")
        
        # 中国象棋棋盘尺寸
        self.cols = 8  # 8列
        self.rows = 10  # 10行
        self.cell_size = 50
        
        # 棋盘状态
        self.board = [[0 for _ in range(self.cols)] for _ in range(self.rows)]
        self.visited = [[False for _ in range(self.cols)] for _ in range(self.rows)]
        self.path = []
        
        # 马的移动方向（中国象棋马的走法，考虑蹩马腿）
        self.moves = [
            (-2, -1), (-2, 1),  # 向上
            (-1, -2), (-1, 2),  # 向左上/右上
            (1, -2), (1, 2),    # 向左下/右下
            (2, -1), (2, 1)     # 向下
        ]
        
        # 蹩马腿的检查位置
        self.blocked_positions = [
            [(-1, 0)],  # 对于(-2, -1)和(-2, 1)，检查上方位置
            [(-1, 0)],
            [(0, -1)],  # 对于(-1, -2)，检查左侧位置
            [(0, 1)],   # 对于(-1, 2)，检查右侧位置
            [(0, -1)],  # 对于(1, -2)，检查左侧位置
            [(0, 1)],   # 对于(1, 2)，检查右侧位置
            [(1, 0)],   # 对于(2, -1)和(2, 1)，检查下方位置
            [(1, 0)]
        ]
        
        # 创建主框架
        self.main_frame = tk.Frame(root)
        self.main_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # 创建控制面板
        self.create_control_panel()
        
        # 创建棋盘画布
        self.create_board_canvas()
        
        # 状态标签
        self.status_label = tk.Label(self.main_frame, text="点击棋盘选择起点，然后点击'开始搜索'按钮", font=("宋体", 12))
        self.status_label.pack(pady=5)
        
        # 当前选择的起点
        self.start_pos = None
        
    def create_control_panel(self):
        """创建控制面板"""
        control_frame = tk.Frame(self.main_frame)
        control_frame.pack(fill=tk.X, pady=(0, 10))
        
        # 起点选择标签
        tk.Label(control_frame, text="起点: ", font=("宋体", 12)).grid(row=0, column=0, padx=5)
        
        # 起点坐标显示
        self.start_label = tk.Label(control_frame, text="未选择", font=("宋体", 12), width=10, relief=tk.SUNKEN)
        self.start_label.grid(row=0, column=1, padx=5)
        
        # 随机起点按钮
        tk.Button(control_frame, text="随机起点", font=("宋体", 10), 
                 command=self.random_start).grid(row=0, column=2, padx=5)
        
        # 清空起点按钮
        tk.Button(control_frame, text="清空起点", font=("宋体", 10), 
                 command=self.clear_start).grid(row=0, column=3, padx=5)
        
        # 开始搜索按钮
        tk.Button(control_frame, text="开始搜索", font=("宋体", 12, "bold"), 
                 bg="lightblue", command=self.start_search).grid(row=0, column=4, padx=20)
        
        # 重置按钮
        tk.Button(control_frame, text="重置棋盘", font=("宋体", 10), 
                 command=self.reset_board).grid(row=0, column=5, padx=5)
        
        # 算法选择
        tk.Label(control_frame, text="算法: ", font=("宋体", 12)).grid(row=0, column=6, padx=5)
        
        self.algorithm_var = tk.StringVar(value="Warnsdorff规则")
        algorithm_menu = ttk.Combobox(control_frame, textvariable=self.algorithm_var, 
                                      values=["Warnsdorff规则", "回溯算法"], 
                                      state="readonly", width=15)
        algorithm_menu.grid(row=0, column=7, padx=5)
        
        # 速度控制
        tk.Label(control_frame, text="速度: ", font=("宋体", 12)).grid(row=0, column=8, padx=5)
        self.speed_var = tk.IntVar(value=50)
        speed_scale = tk.Scale(control_frame, from_=1, to=100, orient=tk.HORIZONTAL, 
                              variable=self.speed_var, length=100, showvalue=0)
        speed_scale.grid(row=0, column=9, padx=5)
        
    def create_board_canvas(self):
        """创建棋盘画布"""
        # 计算画布大小
        self.canvas_width = self.cols * self.cell_size + 100
        self.canvas_height = self.rows * self.cell_size + 100
        
        # 创建画布
        self.canvas = tk.Canvas(self.main_frame, width=self.canvas_width, height=self.canvas_height, 
                               bg="lightyellow", relief=tk.RAISED, bd=2)
        self.canvas.pack()
        
        # 绑定点击事件
        self.canvas.bind("<Button-1>", self.on_canvas_click)
        
        # 绘制棋盘
        self.draw_board()
    
    def draw_board(self):
        """绘制棋盘"""
        # 清空画布
        self.canvas.delete("all")
        
        # 计算偏移量使棋盘居中
        offset_x = 50
        offset_y = 50
        
        # 绘制棋盘格子
        for row in range(self.rows):
            for col in range(self.cols):
                x1 = offset_x + col * self.cell_size
                y1 = offset_y + row * self.cell_size
                x2 = x1 + self.cell_size
                y2 = y1 + self.cell_size
                
                # 创建矩形
                rect = self.canvas.create_rectangle(x1, y1, x2, y2, 
                                                   fill="wheat", outline="black", width=1)
                
                # 存储矩形ID和位置信息
                self.canvas.itemconfig(rect, tags=f"cell_{row}_{col}")
                
                # 显示坐标
                if row == 0 or row == self.rows-1 or col == 0 or col == self.cols-1:
                    coord_text = f"({row},{col})"
                    self.canvas.create_text(x1 + 10, y1 + 10, text=coord_text, 
                                           font=("Arial", 8), fill="gray")
        
        # 绘制楚河汉界
        mid_row = self.rows // 2
        mid_x1 = offset_x
        mid_x2 = offset_x + self.cols * self.cell_size
        mid_y = offset_y + mid_row * self.cell_size
        
        # 绘制分界线
        self.canvas.create_line(mid_x1, mid_y, mid_x2, mid_y, 
                               fill="red", width=2, dash=(5, 5))
        
        # 绘制"楚河"和"汉界"
        font_size = 20
        self.canvas.create_text(mid_x1 + 50, mid_y - font_size, text="楚", 
                               font=("楷体", font_size, "bold"), fill="red")
        self.canvas.create_text(mid_x2 - 50, mid_y - font_size, text="河", 
                               font=("楷体", font_size, "bold"), fill="red")
        self.canvas.create_text(mid_x1 + 50, mid_y + font_size, text="汉", 
                               font=("楷体", font_size, "bold"), fill="red")
        self.canvas.create_text(mid_x2 - 50, mid_y + font_size, text="界", 
                               font=("楷体", font_size, "bold"), fill="red")
        
        # 绘制数字标记
        for i in range(self.rows):
            y = offset_y + i * self.cell_size + self.cell_size // 2
            self.canvas.create_text(offset_x - 20, y, text=str(i), font=("Arial", 10, "bold"))
        
        for i in range(self.cols):
            x = offset_x + i * self.cell_size + self.cell_size // 2
            self.canvas.create_text(x, offset_y - 20, text=str(i), font=("Arial", 10, "bold"))
        
        # 绘制标题
        self.canvas.create_text(self.canvas_width // 2, 20, 
                               text="中国象棋棋盘 - 马步遍历问题", 
                               font=("黑体", 16, "bold"), fill="darkblue")
        
        # 如果已有起点，标记起点
        if self.start_pos:
            self.highlight_start_position()
    
    def on_canvas_click(self, event):
        """处理棋盘点击事件"""
        offset_x = 50
        offset_y = 50
        
        # 计算点击位置对应的行列
        col = (event.x - offset_x) // self.cell_size
        row = (event.y - offset_y) // self.cell_size
        
        # 检查是否在棋盘范围内
        if 0 <= row < self.rows and 0 <= col < self.cols:
            self.start_pos = (row, col)
            self.start_label.config(text=f"({row}, {col})")
            self.status_label.config(text=f"已选择起点: ({row}, {col})，点击'开始搜索'按钮")
            self.highlight_start_position()
    
    def highlight_start_position(self):
        """高亮显示起点位置"""
        if not self.start_pos:
            return
            
        row, col = self.start_pos
        offset_x = 50
        offset_y = 50
        
        x1 = offset_x + col * self.cell_size
        y1 = offset_y + row * self.cell_size
        x2 = x1 + self.cell_size
        y2 = y1 + self.cell_size
        
        # 清除之前的高亮
        self.canvas.delete("start_highlight")
        
        # 绘制高亮
        self.canvas.create_rectangle(x1, y1, x2, y2, 
                                    fill="lightgreen", outline="green", width=3,
                                    tags="start_highlight")
        
        # 绘制"起点"文字
        self.canvas.create_text(x1 + self.cell_size//2, y1 + self.cell_size//2,
                               text="起点", font=("黑体", 12, "bold"),
                               fill="darkgreen", tags="start_highlight")
    
    def random_start(self):
        """随机选择起点"""
        row = random.randint(0, self.rows-1)
        col = random.randint(0, self.cols-1)
        self.start_pos = (row, col)
        self.start_label.config(text=f"({row}, {col})")
        self.status_label.config(text=f"已随机选择起点: ({row}, {col})，点击'开始搜索'按钮")
        self.highlight_start_position()
    
    def clear_start(self):
        """清空起点选择"""
        self.start_pos = None
        self.start_label.config(text="未选择")
        self.status_label.config(text="点击棋盘选择起点，然后点击'开始搜索'按钮")
        self.canvas.delete("start_highlight")
    
    def reset_board(self):
        """重置棋盘"""
        self.board = [[0 for _ in range(self.cols)] for _ in range(self.rows)]
        self.visited = [[False for _ in range(self.cols)] for _ in range(self.rows)]
        self.path = []
        self.draw_board()
        self.status_label.config(text="棋盘已重置，请选择起点")
    
    def is_move_valid(self, row, col, move_idx):
        """检查马的移动是否合法（考虑蹩马腿）"""
        dr, dc = self.moves[move_idx]
        new_row, new_col = row + dr, col + dc
        
        # 检查目标位置是否在棋盘内
        if not (0 <= new_row < self.rows and 0 <= new_col < self.cols):
            return False, None
        
        # 检查目标位置是否已访问
        if self.visited[new_row][new_col]:
            return False, None
        
        # 检查是否蹩马腿
        block_dr, block_dc = self.blocked_positions[move_idx][0]
        block_row, block_col = row + block_dr, col + block_dc
        
        # 蹩马腿位置必须在棋盘内
        if 0 <= block_row < self.rows and 0 <= block_col < self.cols:
            # 蹩马腿位置如果有棋子，则不能移动
            # 这里我们假设没有棋子，因为我们要遍历所有点
            # 在实际象棋中，这里需要检查是否有棋子
            pass
        
        return True, (new_row, new_col)
    
    def get_valid_moves(self, row, col):
        """获取当前位置所有合法移动"""
        valid_moves = []
        for i in range(len(self.moves)):
            is_valid, new_pos = self.is_move_valid(row, col, i)
            if is_valid:
                valid_moves.append((i, new_pos))
        return valid_moves
    
    def count_valid_moves(self, row, col):
        """计算从指定位置可移动到的未访问位置数量（用于Warnsdorff规则）"""
        count = 0
        for i in range(len(self.moves)):
            is_valid, _ = self.is_move_valid(row, col, i)
            if is_valid:
                count += 1
        return count
    
    def warnsdorff_search(self, start_row, start_col):
        """使用Warnsdorff规则进行搜索"""
        # 初始化
        self.visited = [[False for _ in range(self.cols)] for _ in range(self.rows)]
        self.path = []
        
        current_row, current_col = start_row, start_col
        step = 1
        self.board[current_row][current_col] = step
        self.visited[current_row][current_col] = True
        self.path.append((current_row, current_col))
        
        # 更新显示
        self.update_display(current_row, current_col, step)
        
        # 进行移动
        for _ in range(self.rows * self.cols - 1):
            valid_moves = self.get_valid_moves(current_row, current_col)
            
            if not valid_moves:
                break
            
            # 使用Warnsdorff规则：选择下一步可行位置最少的位置
            best_move = None
            min_next_moves = float('inf')
            
            for move_idx, (next_row, next_col) in valid_moves:
                # 计算从下一步位置可移动到的未访问位置数量
                next_moves_count = self.count_valid_moves(next_row, next_col)
                
                if next_moves_count < min_next_moves:
                    min_next_moves = next_moves_count
                    best_move = (next_row, next_col)
            
            if best_move:
                current_row, current_col = best_move
                step += 1
                self.board[current_row][current_col] = step
                self.visited[current_row][current_col] = True
                self.path.append((current_row, current_col))
                
                # 更新显示
                self.update_display(current_row, current_col, step)
                
                # 控制速度
                time.sleep((101 - self.speed_var.get()) / 1000)
                self.root.update()
        
        return step == self.rows * self.cols
    
    def backtrack_search(self, row, col, step):
        """使用回溯算法搜索哈密顿路径"""
        # 标记当前位置
        self.board[row][col] = step
        self.visited[row][col] = True
        self.path.append((row, col))
        
        # 更新显示
        self.update_display(row, col, step)
        
        # 控制速度
        time.sleep((101 - self.speed_var.get()) / 1000)
        self.root.update()
        
        # 如果已经访问了所有位置，返回成功
        if step == self.rows * self.cols:
            return True
        
        # 获取所有合法移动
        valid_moves = self.get_valid_moves(row, col)
        
        # 使用Warnsdorff规则对移动进行排序，加速搜索
        move_scores = []
        for move_idx, (next_row, next_col) in valid_moves:
            # 计算从下一步位置可移动到的未访问位置数量
            next_moves_count = self.count_valid_moves(next_row, next_col)
            move_scores.append((next_moves_count, next_row, next_col))
        
        # 按可行位置数量排序（最少优先）
        move_scores.sort()
        
        # 尝试每个可能的移动
        for _, next_row, next_col in move_scores:
            if self.backtrack_search(next_row, next_col, step + 1):
                return True
        
        # 回溯
        self.board[row][col] = 0
        self.visited[row][col] = False
        self.path.pop()
        
        # 更新显示
        self.update_display(row, col, 0, backtrack=True)
        
        return False
    
    def update_display(self, row, col, step, backtrack=False):
        """更新棋盘显示"""
        offset_x = 50
        offset_y = 50
        
        x1 = offset_x + col * self.cell_size
        y1 = offset_y + row * self.cell_size
        x2 = x1 + self.cell_size
        y2 = y1 + self.cell_size
        
        # 如果回溯，清除该位置
        if backtrack:
            self.canvas.delete(f"cell_text_{row}_{col}")
            self.canvas.delete(f"cell_path_{row}_{col}")
            return
        
        # 清除该位置之前的路径标记（保留起点）
        if (row, col) != self.start_pos:
            self.canvas.delete(f"cell_path_{row}_{col}")
        
        # 绘制访问顺序
        if step > 0:
            # 使用不同颜色表示不同步骤
            color_intensity = min(200, 50 + step * 2)
            color = f"#{min(255, color_intensity):02x}{max(0, 200 - color_intensity//2):02x}{max(0, 150 - color_intensity//3):02x}"
            
            # 绘制背景色
            self.canvas.create_rectangle(x1, y1, x2, y2, 
                                        fill=color, outline="black", width=1,
                                        tags=f"cell_path_{row}_{col}")
            
            # 绘制步骤数字
            self.canvas.create_text(x1 + self.cell_size//2, y1 + self.cell_size//2,
                                   text=str(step), font=("Arial", 10, "bold"),
                                   fill="black", tags=f"cell_text_{row}_{col}")
    
    def start_search(self):
        """开始搜索"""
        if not self.start_pos:
            messagebox.showwarning("警告", "请先选择起点！")
            return
        
        # 重置棋盘
        self.board = [[0 for _ in range(self.cols)] for _ in range(self.rows)]
        self.visited = [[False for _ in range(self.cols)] for _ in range(self.rows)]
        self.path = []
        
        # 重新绘制棋盘
        self.draw_board()
        
        # 获取起点
        start_row, start_col = self.start_pos
        
        # 根据选择的算法进行搜索
        algorithm = self.algorithm_var.get()
        success = False
        
        if algorithm == "Warnsdorff规则":
            self.status_label.config(text="正在使用Warnsdorff规则搜索路径...")
            self.root.update()
            success = self.warnsdorff_search(start_row, start_col)
        else:  # 回溯算法
            self.status_label.config(text="正在使用回溯算法搜索路径...")
            self.root.update()
            success = self.backtrack_search(start_row, start_col, 1)
        
        # 显示结果
        if success:
            self.status_label.config(text=f"成功找到路径！共访问了{len(self.path)}个点")
            
            # 绘制路径线
            self.draw_path_lines()
        else:
            self.status_label.config(text=f"未能找到完整路径，只访问了{len(self.path)}个点")
            
            # 显示访问过的点
            for i, (row, col) in enumerate(self.path):
                self.update_display(row, col, i+1)
    
    def draw_path_lines(self):
        """绘制路径连线"""
        offset_x = 50
        offset_y = 50
        
        # 清除之前的路径线
        self.canvas.delete("path_line")
        
        # 绘制路径连线
        for i in range(len(self.path) - 1):
            row1, col1 = self.path[i]
            row2, col2 = self.path[i+1]
            
            x1 = offset_x + col1 * self.cell_size + self.cell_size // 2
            y1 = offset_y + row1 * self.cell_size + self.cell_size // 2
            x2 = offset_x + col2 * self.cell_size + self.cell_size // 2
            y2 = offset_y + row2 * self.cell_size + self.cell_size // 2
            
            # 计算线条颜色（渐变色）
            color_value = min(255, 100 + i * 3)
            color = f"#{color_value:02x}{max(0, 150 - i//2):02x}{max(0, 200 - i):02x}"
            
            self.canvas.create_line(x1, y1, x2, y2, 
                                   fill=color, width=2, 
                                   tags="path_line", arrow=tk.LAST)
            
            # 控制绘制速度
            time.sleep(0.01)
            self.root.update()

def main():
    """主函数"""
    root = tk.Tk()
    app = ChineseChessBoard(root)
    root.mainloop()

if __name__ == "__main__":
    main()
