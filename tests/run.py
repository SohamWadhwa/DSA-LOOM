"""Shared correctness suite for every approach. Python standard library only."""
from __future__ import annotations

import argparse
from collections import Counter, deque
import copy
import importlib.util
import itertools
import json
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
CATALOG = json.loads((ROOT / 'catalog.json').read_text(encoding='utf-8'))


class ListNode:
    def __init__(self, val=0, next=None):
        self.val, self.next = val, next


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val, self.left, self.right = val, left, right


def linked(values):
    nodes = [ListNode(value) for value in values]
    for a, b in zip(nodes, nodes[1:]):
        a.next = b
    return (nodes[0] if nodes else None), nodes


def tree(values):
    if not values:
        return None
    root = TreeNode(values[0])
    pending = deque([root])
    index = 1
    while pending and index < len(values):
        parent = pending.popleft()
        for attr in ('left', 'right'):
            if index < len(values) and values[index] is not None:
                child = TreeNode(values[index])
                setattr(parent, attr, child)
                pending.append(child)
            index += 1
    return root


def oracle(number, args):
    if number == 1:
        nums, target = args
        return next([i, j] for i in range(len(nums)) for j in range(i + 1, len(nums))
                    if nums[i] + nums[j] == target)
    if number == 20:
        s = args[0]
        while any(pair in s for pair in ('()', '[]', '{}')):
            for pair in ('()', '[]', '{}'):
                s = s.replace(pair, '')
        return not s
    if number == 704:
        nums, target = args
        return nums.index(target) if target in nums else -1
    if number == 206:
        return args[0][::-1]
    if number == 102:
        root = tree(args[0])
        result, pending = [], deque([(root, 0)] if root else [])
        while pending:
            node, depth = pending.popleft()
            if depth == len(result):
                result.append([])
            result[depth].append(node.val)
            for child in (node.left, node.right):
                if child:
                    pending.append((child, depth + 1))
        return result
    if number == 200:
        grid = args[0]
        land = {(r, c) for r, row in enumerate(grid) for c, value in enumerate(row) if value == '1'}
        count = 0
        while land:
            count += 1
            stack = [land.pop()]
            while stack:
                r, c = stack.pop()
                for cell in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
                    if cell in land:
                        land.remove(cell)
                        stack.append(cell)
        return count
    if number == 78:
        return sorted(tuple(sorted(part)) for size in range(len(args[0]) + 1)
                      for part in itertools.combinations(args[0], size))
    if number == 322:
        coins, amount = args
        pending, seen = deque([(0, 0)]), {0}
        while pending:
            value, distance = pending.popleft()
            if value == amount:
                return distance
            for coin in coins:
                nxt = value + coin
                if nxt <= amount and nxt not in seen:
                    seen.add(nxt)
                    pending.append((nxt, distance + 1))
        return -1
    if number == 23:
        return sorted(itertools.chain.from_iterable(args[0]))
    if number == 42:
        heights = args[0]
        return sum(max(0, min(max(heights[:i + 1]), max(heights[i:])) - height)
                   for i, height in enumerate(heights))
    if number == 76:
        s, t = args
        if not t:
            return ''
        need = Counter(t)
        for length in range(len(t), len(s) + 1):
            for start in range(len(s) - length + 1):
                window = s[start:start + length]
                have = Counter(window)
                if all(have[ch] >= count for ch, count in need.items()):
                    return window
        return ''
    if number == 84:
        heights = args[0]
        return max((min(heights[left:right + 1]) * (right - left + 1)
                    for left in range(len(heights)) for right in range(left, len(heights))), default=0)
    raise AssertionError(number)


def cases():
    """Fixed examples plus seeded random cases, identical across all languages."""
    data = {
        1: [([2, 7, 11, 15], 9), ([3, 3], 6), ([-4, 1, 6, 10], 2),
            ([-1000000000, 1000000000], 0), ([0, 4, 3, 0], 0)],
        20: [('()',), ('()[]{}',), ('(]',), ('([])',), ('([)]',), ('(',), (')',), ('((()))',)],
        704: [([-1, 0, 3, 5, 9, 12], 9), ([-1, 0, 3, 5, 9, 12], 2), ([7], 7), ([7], 6),
              ([1, 3], 1), ([1, 3], 3), ([1, 3], 0), ([1, 3], 4)],
        206: [([],), ([1],), ([1, 2],), ([1, 2, 3, 4, 5],), ([2, 2, -1],)],
        102: [([],), ([1],), ([3, 9, 20, None, None, 15, 7],), ([1, None, 2, None, 3],),
              ([1, 2, 3, 4, 5, 6, 7],)],
        200: [([list('11110'), list('11010'), list('11000'), list('00000')],),
              ([list('11000'), list('11000'), list('00100'), list('00011')],),
              ([list('0')],), ([list('1')],), ([list('10'), list('01')],),
              ([list('11111')],), ([list('1'), list('0'), list('1')],)],
        78: [([1, 2, 3],), ([0],), ([-2, 0, 3],), ([4, -1],)],
        322: [([1, 2, 5], 11), ([2], 3), ([1], 0), ([1, 3, 4], 6),
              ([2, 5], 7), ([2147483647], 2), ([2, 4], 7)],
        23: [([[1, 4, 5], [1, 3, 4], [2, 6]],), ([],), ([[]],),
             ([[], [-5, -1, 0], [], [-5, 2]],), ([[1], [1], [1]],)],
        42: [([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1],), ([4, 2, 0, 3, 2, 5],),
             ([0],), ([3, 3, 3],), ([0, 1, 2, 3],), ([3, 2, 1, 0],), ([3, 0, 3],)],
        76: [('ADOBECODEBANC', 'ABC'), ('a', 'a'), ('a', 'aa'), ('AAABBC', 'AABC'),
             ('aA', 'A'), ('ZZZ', 'A'), ('ABBAAC', 'AAC')],
        84: [([2, 1, 5, 6, 2, 3],), ([2, 4],), ([0],), ([2, 2, 2],),
             ([1, 2, 3, 4],), ([4, 3, 2, 1],), ([0, 3, 0, 3],)],
    }
    rng = random.Random(20261028)
    for _ in range(30):
        # Admit only arrays with exactly one valid pair, matching LeetCode's contract.
        while True:
            nums = [rng.randint(-12, 12) for _ in range(rng.randint(2, 9))]
            i, j = rng.sample(range(len(nums)), 2)
            target = nums[i] + nums[j]
            pairs = [(a, b) for a in range(len(nums)) for b in range(a + 1, len(nums))
                     if nums[a] + nums[b] == target]
            if len(pairs) == 1:
                break
        data[1].append((nums, target))
        data[20].append((''.join(rng.choice('()[]{}') for _ in range(rng.randint(1, 14))),))
        values = sorted(rng.sample(range(-25, 26), rng.randint(1, 12)))
        data[704].append((values, rng.randint(-28, 28)))
        data[206].append(([rng.randint(-5, 5) for _ in range(rng.randint(0, 14))],))
        values = [rng.randint(-5, 5)]
        parents = 1
        while parents and len(values) < 21:
            parents -= 1
            for _child in range(2):
                value = rng.randint(-5, 5) if rng.random() < .65 else None
                values.append(value)
                parents += value is not None
        data[102].append((values,))
        rows, cols = rng.randint(1, 5), rng.randint(1, 5)
        data[200].append(([[rng.choice('01') for _ in range(cols)] for _ in range(rows)],))
        data[78].append((rng.sample(range(-10, 11), rng.randint(1, 7)),))
        data[322].append((rng.sample(range(1, 8), rng.randint(1, 4)), rng.randint(0, 11)))
        data[23].append(([sorted(rng.randint(-5, 5) for _ in range(rng.randint(0, 7)))
                          for _ in range(rng.randint(0, 7))],))
        heights = [rng.randint(0, 8) for _ in range(rng.randint(1, 12))]
        data[42].append((heights,))
        data[84].append((heights,))
        data[76].append((''.join(rng.choice('ABCa') for _ in range(rng.randint(1, 10))),
                         ''.join(rng.choice('ABCa') for _ in range(rng.randint(1, 4)))))
    # Defensive empty-input checks beyond some original problem constraints.
    for number in (20, 42, 78, 84, 200):
        data[number].append(('',) if number == 20 else ([],))
    data[704].append(([], 3))
    data[76].extend([('', 'A'), ('ABC', '')])
    return data


def python_call(problem, module, args, expected):
    number = problem['id']
    prepared = copy.deepcopy(args)
    nodes = []
    if number == 206:
        head, nodes = linked(args[0])
        prepared = (head,)
    elif number == 23:
        heads = []
        for values in args[0]:
            head, allocated = linked(values)
            heads.append(head)
            nodes.extend(allocated)
        prepared = (heads,)
    elif number == 102:
        prepared = (tree(args[0]),)
    result = getattr(module.Solution(), problem['method'])(*prepared)
    if number in (206, 23):
        values, seen = [], set()
        while result is not None:
            assert id(result) not in seen, 'cycle in linked list'
            seen.add(id(result))
            values.append(result.val)
            result = result.next
        assert seen == {id(node) for node in nodes}, 'nodes lost or replaced'
        result = values
    elif number == 1:
        assert len(result) == 2 and result[0] != result[1]
        assert all(0 <= i < len(args[0]) for i in result)
        assert sum(args[0][i] for i in result) == args[1]
        result = sorted(result)
    elif number == 78:
        result = sorted(tuple(sorted(part)) for part in result)
    assert result == expected, (problem['slug'], args, result, expected)
    if number not in (206, 23, 102):
        assert prepared == args, 'unexpected input mutation'


def python_stress(problem, module):
    number = problem['id']
    if number == 1:
        args, expected = ([0] + [100] * 9998 + [1], 1), [0, 9999]
    elif number == 20:
        args, expected = ('(' * 5000 + ')' * 5000,), True
    elif number == 704:
        args, expected = (list(range(-5000, 5000)), 4999), 9999
    elif number == 206:
        args, expected = (list(range(5000)),), list(reversed(range(5000)))
    elif number == 102:
        args = ([0] + [item for i in range(1, 2000) for item in (None, i)],)
        expected = [[i] for i in range(2000)]
    elif number == 200:
        args, expected = ([['1'] * 300 for _ in range(300)],), 1
    elif number == 78:
        args = (list(range(10)),)
        expected = oracle(number, args)
    elif number == 322:
        args, expected = ([1, 7, 10], 10000), 1000
    elif number == 23:
        args = ([[i] for i in range(10000)],)
        expected = list(range(10000))
    elif number == 42:
        args, expected = ([100000] + [0] * 19998 + [100000],), 1999800000
    elif number == 76:
        args, expected = ('A' * 99999 + 'B', 'AB'), 'AB'
    elif number == 84:
        args, expected = ([10000] * 100000,), 1000000000
    python_call(problem, module, args, expected)


def literal(values):
    return '{' + ','.join(str(value) for value in values) + '}'


def c_array(name, values, kind='int'):
    return f'{kind} {name}[] = {literal(values) if values else "{0}"};\n'


def native_case(problem, args, expected, cpp):
    """Generate small native test blocks without a third-party JSON library."""
    number, method = problem['id'], problem['method']
    lines = []
    call = ('Solution().' + method) if cpp else method
    if number in (1, 704, 322, 42, 84, 78):
        nums = args[0]
        lines.append(f'vector<int> nums = {literal(nums)};' if cpp else c_array('nums', nums))
        extra = f', {args[1]}' if number in (1, 704, 322) else ''
        if cpp:
            lines.append(f'auto result = {call}(nums{extra});')
        elif number == 1:
            lines.append(f'int size = 0; int* result = {call}(nums, {len(nums)}{extra}, &size);')
        elif number == 78:
            lines.append(f'int size = 0, *columns = NULL; int** result = {call}(nums, {len(nums)}, &size, &columns);')
        else:
            lines.append(f'int result = {call}(nums, {len(nums)}{extra});')
        if number == 1:
            lines.append('CHECK(result.size() == 2);' if cpp else 'CHECK(size == 2 && result != NULL);')
            lines.append(f'CHECK(result[0] >= 0 && result[0] < {len(nums)} && result[1] >= 0 && result[1] < {len(nums)});')
            lines.append(f'CHECK(result[0] != result[1] && (long long)nums[result[0]] + nums[result[1]] == {args[1]});')
            if not cpp:
                lines.append('free(result);')
        elif number == 78:
            total = 1 << len(nums)
            lines.append(f'CHECK({"result.size()" if cpp else "size"} == {total});')
            lines.append(f'bool masks[{total}] = {{false}};')
            lines.append(f'for (int r = 0; r < {total}; ++r) {{ int mask = 0;')
            width = 'static_cast<int>(result[r].size())' if cpp else 'columns[r]'
            lines.append(f'for (int c = 0; c < {width}; ++c) {{ int bit = -1;')
            lines.append(f'for (int i = 0; i < {len(nums)}; ++i) if (nums[i] == result[r][c]) bit = i;')
            lines.append('CHECK(bit >= 0); CHECK(!(mask & (1 << bit))); mask |= 1 << bit; }')
            lines.append('CHECK(!masks[mask]); masks[mask] = true;')
            if not cpp:
                lines.append('free(result[r]);')
            lines.append('}')
            if not cpp:
                lines.append('free(result); free(columns);')
        else:
            lines.append(f'CHECK(result == {expected});')
        # All of these implementations promise to preserve the input array.
        lines.append(c_array('original', nums))
        lines.append(f'for (int i = 0; i < {len(nums)}; ++i) CHECK(nums[i] == original[i]);')
    elif number in (20, 76):
        lines.append(f'{"string" if cpp else "char"} s{ " = " if cpp else "[] = "}{json.dumps(args[0])};')
        if number == 20:
            lines.append(f'CHECK({call}(s) == {str(expected).lower()});')
        else:
            lines.append(f'{"string" if cpp else "char"} t{ " = " if cpp else "[] = "}{json.dumps(args[1])};')
            lines.append(f'{"string" if cpp else "char*"} result = {call}(s, t);')
            lines.append(f'CHECK(result == {json.dumps(expected)});' if cpp else
                         f'CHECK(strcmp(result, {json.dumps(expected)}) == 0); free(result);')
            lines.append(f'CHECK(t == {json.dumps(args[1])});' if cpp else
                         f'CHECK(strcmp(t, {json.dumps(args[1])}) == 0);')
        lines.append(f'CHECK(s == {json.dumps(args[0])});' if cpp else
                     f'CHECK(strcmp(s, {json.dumps(args[0])}) == 0);')
    elif number in (206, 23):
        groups = [args[0]] if number == 206 else args[0]
        flat = list(itertools.chain.from_iterable(groups))
        node_type = 'ListNode' if cpp else 'struct ListNode'
        lines.append(f'{node_type} nodes[{max(1, len(flat))}];')
        lines.append(c_array('values', flat))
        lines.append(f'for (int i = 0; i < {len(flat)}; ++i) {{ nodes[i].val = values[i]; nodes[i].next = NULL; }}')
        starts, offset = [], 0
        for group in groups:
            starts.append(f'&nodes[{offset}]' if group else 'NULL')
            for i in range(offset, offset + len(group) - 1):
                lines.append(f'nodes[{i}].next = &nodes[{i + 1}];')
            offset += len(group)
        if number == 206:
            lines.append(f'{node_type}* result = {call}({starts[0]});')
        else:
            initialization = '{' + ','.join(starts or ['NULL']) + '}'
            lines.append(f'vector<ListNode*> heads = {"{" + ",".join(starts) + "}"};' if cpp else
                         f'{node_type}* heads[] = {initialization};')
            lines.append(f'{node_type}* result = {call}(heads{ "" if cpp else ", " + str(len(groups))});')
        lines.append(c_array('expected', expected))
        lines.append(f'bool visited[{max(1, len(flat))}] = {{false}};')
        lines.append(f'for (int i = 0; i < {len(flat)}; ++i) {{ CHECK(result != NULL); CHECK(result->val == expected[i]); int found = -1;')
        lines.append(f'for (int j = 0; j < {len(flat)}; ++j) if (result == &nodes[j]) found = j;')
        lines.append('CHECK(found >= 0); CHECK(!visited[found]); visited[found] = true; result = result->next; } CHECK(result == NULL);')
    elif number == 102:
        values = args[0]
        node_type = 'TreeNode' if cpp else 'struct TreeNode'
        count = sum(v is not None for v in values)
        lines.append(f'{node_type} nodes[{max(1, count)}];')
        if count:
            lines.append(f'nodes[0].val = {values[0]}; nodes[0].left = nodes[0].right = NULL;')
        pending, index, allocated = deque([0] if count else []), 1, 1
        while pending and index < len(values):
            parent = pending.popleft()
            for attr in ('left', 'right'):
                if index < len(values) and values[index] is not None:
                    lines.append(f'nodes[{allocated}].val = {values[index]}; nodes[{allocated}].left = nodes[{allocated}].right = NULL;')
                    lines.append(f'nodes[{parent}].{attr} = &nodes[{allocated}];')
                    pending.append(allocated)
                    allocated += 1
                index += 1
        root = '&nodes[0]' if count else 'NULL'
        lines.append(f'auto result = {call}({root});' if cpp else
                     f'int size = 0, *columns = NULL; int** result = {call}({root}, &size, &columns);')
        lines.append(f'CHECK({"result.size()" if cpp else "size"} == {len(expected)});')
        for r, row in enumerate(expected):
            lines.append(f'CHECK({f"result[{r}].size()" if cpp else f"columns[{r}]"} == {len(row)});')
            for c, value in enumerate(row):
                lines.append(f'CHECK(result[{r}][{c}] == {value});')
            if not cpp:
                lines.append(f'free(result[{r}]);')
        if not cpp:
            lines.append('free(result); free(columns);')
        if not count:
            lines.append('(void)nodes;')
    elif number == 200:
        grid = args[0]
        if cpp:
            rows = ['{' + ','.join("'" + c + "'" for c in row) + '}' for row in grid]
            lines.append('vector<vector<char>> grid = {' + ','.join(rows) + '};')
            lines.append(f'CHECK({call}(grid) == {expected});')
        else:
            for r, row in enumerate(grid):
                lines.append(f'char row{r}[] = {json.dumps("".join(row))};')
            lines.append('char* grid[] = {' + (','.join(f'row{r}' for r in range(len(grid))) or 'NULL') + '};')
            lines.append(c_array('columns', [len(row) for row in grid]))
            lines.append(f'CHECK({call}(grid, {len(grid)}, columns) == {expected});')
        for r, row in enumerate(grid):
            for c, value in enumerate(row):
                lines.append(f"CHECK(grid[{r}][{c}] == '{value}');")
    return '{\n' + '\n'.join(lines) + '\n}\n'


def native_stress(problem, cpp):
    number, method = problem['id'], problem['method']
    call = ('Solution().' + method) if cpp else method
    alloc = lambda name, n, val: (f'vector<int> {name}({n}, {val});' if cpp else
        f'int* {name} = malloc((size_t){n} * sizeof(int)); for (int i = 0; i < {n}; ++i) {name}[i] = {val};')
    cleanup = '' if cpp else 'free(nums);'
    if number == 1:
        body = alloc('nums', 10000, 100) + 'nums[0] = 0; nums[9999] = 1;'
        body += f'auto result = {call}(nums, 1); CHECK(result.size() == 2);' if cpp else f'int size; int* result = {call}(nums, 10000, 1, &size); CHECK(size == 2);'
        body += 'CHECK((result[0] == 0 && result[1] == 9999) || (result[0] == 9999 && result[1] == 0));'
        if not cpp:
            body += 'free(result);'
        body += cleanup
    elif number == 20:
        body = 'char s[10001]; for (int i = 0; i < 5000; ++i) { s[i] = \'(\'; s[i+5000] = \')\'; } s[10000] = 0;'
        body += f'CHECK({call}(s));'
    elif number in (704, 42, 84):
        n = {704:10000, 42:20000, 84:100000}[number]
        body = alloc('nums', n, 10000 if number == 84 else 0)
        if number == 704:
            body += 'for (int i = 0; i < 10000; ++i) nums[i] = i - 5000;'
            body += f'CHECK({call}(nums{ "" if cpp else ", 10000"}, 4999) == 9999);'
        else:
            if number == 42:
                body += 'nums[0] = nums[19999] = 100000;'
            body += f'CHECK({call}(nums{ "" if cpp else ", " + str(n)}) == {1999800000 if number == 42 else 1000000000});'
        body += cleanup
    elif number == 322:
        body = 'vector<int> nums = {1,7,10};' if cpp else 'int nums[] = {1,7,10};'
        body += f'CHECK({call}(nums{ "" if cpp else ", 3"}, 10000) == 1000);'
    elif number in (206, 23):
        n = 5000 if number == 206 else 10000
        typ = 'ListNode' if cpp else 'struct ListNode'
        body = f'{typ}* nodes = {"new ListNode[" + str(n) + "]" if cpp else "malloc(" + str(n) + " * sizeof(*nodes))"};'
        body += f'for (int i = 0; i < {n}; ++i) {{ nodes[i].val = i; nodes[i].next = {"i + 1 < 5000 ? &nodes[i + 1] : NULL" if number == 206 else "NULL"}; }}'
        if number == 206:
            body += f'{typ}* result = {call}(nodes);'
        else:
            body += 'vector<ListNode*> heads(10000);' if cpp else 'struct ListNode** heads = malloc(10000 * sizeof(*heads));'
            body += 'for (int i = 0; i < 10000; ++i) heads[i] = &nodes[i];'
            body += f'{typ}* result = {call}(heads{ "" if cpp else ", 10000"});'
        body += f'for (int i = 0; i < {n}; ++i) {{ CHECK(result == &nodes[{str(n - 1) + " - i" if number == 206 else "i"}]); result = result->next; }} CHECK(result == NULL);'
        body += 'delete[] nodes;' if cpp else 'free(nodes);'
        if number == 23 and not cpp:
            body += 'free(heads);'
    elif number == 102:
        typ = 'TreeNode' if cpp else 'struct TreeNode'
        body = f'{typ}* nodes = {"new TreeNode[2000]" if cpp else "malloc(2000 * sizeof(*nodes))"};'
        body += 'for (int i = 0; i < 2000; ++i) { nodes[i].val = i; nodes[i].left = NULL; nodes[i].right = i+1 < 2000 ? &nodes[i+1] : NULL; }'
        body += f'auto result = {call}(nodes); CHECK(result.size() == 2000);' if cpp else f'int size, *columns; int** result = {call}(nodes, &size, &columns); CHECK(size == 2000);'
        body += 'for (int i = 0; i < 2000; ++i) {'
        body += 'CHECK(result[i].size() == 1);' if cpp else 'CHECK(columns[i] == 1);'
        body += 'CHECK(result[i][0] == i);'
        if not cpp:
            body += 'free(result[i]);'
        body += '}'
        body += 'delete[] nodes;' if cpp else 'free(nodes); free(result); free(columns);'
    elif number == 200:
        body = 'vector<vector<char>> grid(300, vector<char>(300, \'1\'));' if cpp else 'char** grid = malloc(300 * sizeof(*grid)); int columns[300]; for (int i=0;i<300;++i) { grid[i]=malloc(300); memset(grid[i], \'1\', 300); columns[i]=300; }'
        body += f'CHECK({call}(grid{ "" if cpp else ", 300, columns"}) == 1);'
        if not cpp:
            body += 'for (int i=0;i<300;++i) free(grid[i]); free(grid);'
    elif number == 78:
        return native_case(problem, (list(range(10)),), None, cpp)
    elif number == 76:
        body = 'string s(100000, \'A\'); s.back() = \'B\'; string t = "AB";' if cpp else 'char* s = malloc(100001); memset(s, \'A\', 100000); s[99999] = \'B\'; s[100000] = 0; char t[] = "AB";'
        body += f'CHECK({call}(s,t) == "AB");' if cpp else f'char* result = {call}(s,t); CHECK(strcmp(result,"AB") == 0); free(result); free(s);'
    else:
        return ''
    return '{\n' + body + '\n}\n'


def structural_checks():
    assert len(CATALOG) == 12
    assert Counter(p['difficulty'] for p in CATALOG) == {'Easy':4, 'Medium':4, 'Hard':4}
    for problem in CATALOG:
        directory = ROOT / problem['path']
        lesson = (directory / 'README.md').read_text(encoding='utf-8')
        for section in ('Question Explanation', 'Approaches', 'Edge Cases', 'Sources'):
            assert section in lesson, (problem['slug'], section)
        for approach in problem['approaches']:
            for language, extension in [('c','c'), ('cpp','cpp'), ('python','py')]:
                assert (directory / language / (approach['name'] + '.' + extension)).is_file()
    for doc in ROOT.rglob('*.md'):
        for target in re.findall(r'\]\(([^)]+)\)', doc.read_text(encoding='utf-8')):
            if target.startswith(('http:', 'https:', '#', 'mailto:')):
                continue
            path = target.split('#')[0]
            assert (doc.parent / path).exists(), (doc.relative_to(ROOT), target)


def run_native(problem, approach, data, language, build_dir, sanitize):
    cpp = language == 'cpp'
    configured = os.environ.get('CXX' if cpp else 'CC', 'g++' if cpp else 'gcc')
    compiler = [configured] if Path(configured).is_file() else shlex.split(configured)
    extension = 'cpp' if cpp else 'c'
    solution = (ROOT / problem['path'] / language / (approach['name'] + '.' + extension)).as_posix()
    header = '''#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL line %d: %s\\n", __LINE__, #x); abort(); } } while (0)
'''
    if cpp:
        header += '''#include <vector>
#include <string>
using namespace std;
struct ListNode { int val; ListNode* next; ListNode(int v=0, ListNode* n=nullptr): val(v), next(n) {} };
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v=0): val(v), left(nullptr), right(nullptr) {} };
'''
    else:
        header += 'struct ListNode { int val; struct ListNode* next; };\nstruct TreeNode { int val; struct TreeNode *left, *right; };\n'
    body = ''.join(native_case(problem, args, oracle(problem['id'], args), cpp) for args in data)
    if approach['name'] == 'optimal':
        body += native_stress(problem, cpp)
    source = build_dir / f'{problem["id"]}_{language}_{approach["name"]}.{extension}'
    binary = source.with_suffix('.exe' if os.name == 'nt' else '.out')
    source.write_text(header + f'#include "{solution}"\nint main(void) {{\n' + body + 'return 0;\n}\n')
    flags = ['-std=c++17' if cpp else '-std=c17', '-Wall', '-Wextra', '-Werror', '-O1', '-g']
    if sanitize:
        flags += ['-fsanitize=address' if os.name == 'nt' else '-fsanitize=address,undefined', '-fno-omit-frame-pointer']
    subprocess.run(compiler + flags + [str(source), '-o', str(binary)], check=True, timeout=90)
    env = os.environ.copy()
    env['ASAN_OPTIONS'] = 'detect_leaks=0' if os.name == 'nt' else 'detect_leaks=1'
    subprocess.run([str(binary)], check=True, timeout=30, env=env)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--languages', nargs='+', choices=['python', 'c', 'cpp'], default=['python', 'c', 'cpp'])
    parser.add_argument('--sanitize', action='store_true')
    args = parser.parse_args()
    structural_checks()
    data = cases()
    build_dir = ROOT / '.build'
    build_dir.mkdir(exist_ok=True)
    implementations, checks = 0, 0
    for problem in CATALOG:
        for approach in problem['approaches']:
            for language in args.languages:
                if language == 'python':
                    path = ROOT / problem['path'] / 'python' / (approach['name'] + '.py')
                    spec = importlib.util.spec_from_file_location(f'solution_{problem["id"]}_{approach["name"]}', path)
                    module = importlib.util.module_from_spec(spec)
                    module.ListNode, module.TreeNode = ListNode, TreeNode
                    spec.loader.exec_module(module)
                    for case in data[problem['id']]:
                        python_call(problem, module, case, oracle(problem['id'], case))
                    if approach['name'] == 'optimal':
                        python_stress(problem, module)
                else:
                    run_native(problem, approach, data[problem['id']], language, build_dir, args.sanitize)
                implementations += 1
                checks += len(data[problem['id']]) + (approach['name'] == 'optimal')
                print(f'PASS {problem["id"]:04d} {language:6} {approach["name"]}', flush=True)
    print(f'PASS: {implementations} implementations; {checks} case executions; structure and links valid.')


if __name__ == '__main__':
    main()
