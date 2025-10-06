import json
with open('levels.json', 'r') as f:
    data = json.load(f)
if 'levels' in data and len(data['levels']) > 0:
    base = data['levels'][0]
    new_levels = []
    for i in range(5):
        level = json.loads(json.dumps(base))
        level['ballSpeed'] = 3 + i * 0.5
        if 'bricks' in level:
            r = len(level['bricks'])
            c = len(level['bricks'][0]) if r > 0 else 5
            level['bricks'] = [[1]*(c+i) for _ in range(r+i)]
        new_levels.append(level)
    data['levels'] = new_levels
else:
    data = {'levels': [{'ballSpeed': 3+i*0.5, 'bricks': [[1]*(5+i) for _ in range(3+i)]} for i in range(5)]}
with open('levels.json', 'w') as f:
    json.dump(data, f, indent=2)
print('Done! Total levels:', len(data['levels']))
