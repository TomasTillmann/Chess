from stockfish import Stockfish

stockfish = Stockfish(path='C:/Program Files (x86)/stockfish_15.1_win_x64/stockfish_15.1_win_x64/stockfish-windows-2022-x86-64.exe')

stockfish.set_fen_position("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ")
print(stockfish.get_board_visual())

kwargs = {
    "limit" : 4,
    "limitType": "perft"
}

params = Stockfish.BenchmarkParameters(**kwargs)
print(stockfish.get_parameters())
print(stockfish.benchmark(params))
