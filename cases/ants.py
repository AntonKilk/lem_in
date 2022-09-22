#!/usr/bin/env python3
from collections import defaultdict
import sys

_ANTS, _ROOMS, _LINKS, _START, _END = None, None, None, None, None

def available_from(room):
    for i,_ in enumerate(_ROOMS):
        if _LINKS[room][i]:
            yield i

def read_data():
    ants, start, end = None, None, None
    rooms = []
    links = defaultdict(list)
    next_is = None
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        if line.startswith("##"):
            next_is = line[2:]
            continue
        if line.startswith("#"):
            continue
        if ants is None:
            ants = int(line)
            continue
        if ' ' in line:
            name, _, _ = line.split()
            rooms.append(name)
            if next_is == "start":
                start = name
            elif next_is == "end":
                end = name
            next_is = None
        else:
            f,t = line.split('-')
            links[f].append(t)
            links[t].append(f)
    n_rooms = len(rooms)
    r2i = {f:i for i,f in enumerate(rooms)}
    lnk = [None] * n_rooms
    for i,f in enumerate(rooms):
        lnk[i] = [0] * n_rooms
        for t in links[f]:
            lnk[i][r2i[t]] = 1
    return ants, r2i[start], r2i[end], rooms, lnk

def find_lengths(starts, solution):
    result = []
    for s in starts:
        l = 1
        assert solution[s] is not None
        while solution[s] != _END:
            l += 1
            s = solution[s]
        result.append(l)
    print("Length:", l)
    return result

def evaluate(lengths):
    ants = _ANTS
    d = 1
    result = lengths[0]
    for p1, p2 in zip(lengths, lengths[1:]):
        moved = (p2-p1)*d
        if ants <= moved:
            break
        ants -= moved
        result += p2-p1
        d += 1
    result += ants // d
    if ants % d:
        result += 1
    return result

def evaluate_solution(starts, solution):
    print("Reached end. Starts:", *(_ROOMS[s] for s in starts))
    lengths = find_lengths(starts, solution)
    result = evaluate(lengths)
    other = solve_from(starts[:], solution[:], _START)
    if other[0] is not None and other[0] < result:
        return other
    return result, starts, solution

def solve_from(starts, solution, current_room=None):
    if current_room is None:
        current_room = _START
    best, best_starts, best_solution = None, None, None
    for next_room in available_from(current_room):
        if solution[next_room] is not None or next_room == _START:
            continue
        print(f"Trying link {_ROOMS[current_room]}->{_ROOMS[next_room]}")
        if next_room == _END:
            solution[current_room] = _END
            result = evaluate_solution(starts, solution)
        else:
            if current_room == _START:
                starts.append(next_room)
            else:
                solution[current_room] = next_room
            result = solve_from(starts, solution, next_room)
            if current_room == _START:
                starts.pop()
            else:
                solution[current_room] = None
        if result[0] is not None and (best is None or result[0] < best):
            best, best_starts, best_solution = result[0], result[1][:], result[2][:]
    solution[current_room] = None
    return best, best_starts, best_solution

def main():
    global _ANTS, _ROOMS, _LINKS, _START, _END
    _ANTS, _START, _END, _ROOMS, _LINKS  = read_data()
    turns, starts, solution = solve_from([], [None] * len(_ROOMS))
    print("Turns:", turns)
    print("Paths:")
    for s in starts:
        print("  ", end="")
        while True:
            print(_ROOMS[s], end='')
            if s == _END:
                print()
                break
            else:
                print('->', end='')
            s = solution[s]

if __name__ == '__main__':
    main()
