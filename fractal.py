import multiprocessing as mp

from matplotlib import pyplot as plt
from tqdm import tqdm


def is_converge(c: complex, max_iter: int = 10000) -> (bool, int, int):
    z = 0
    counter = 0
    oscillate = set()
    while counter < max_iter:
        oscillate.add(z)
        z = z ** 2 + c
        counter += 1
        if z in oscillate:
            return True, counter, c
        elif abs(z) > 2:
            return False, counter, c
    return False, -1, c


def get_fractal(x_range: tuple, density) -> dict:
    """
    Time Complexity : O(max_iter * (density ** 2))
    """
    ret = {'stable': dict(), 'unstable': dict()}
    _range = abs(x_range[1] - x_range[0])
    r_gap = _range / density
    i_gap = 3 / density
    points = []
    a = x_range[0]
    for _ in range(density + 1):
        b = -1.5
        for _ in range(density + 1):
            points.append(complex(a, b))
            b += i_gap
        a += r_gap
    with mp.Pool(processes=30) as pool:
        for stable, count, c in tqdm(pool.imap_unordered(is_converge, points, chunksize=65535), total=len(points)):
            if stable:
                if count in ret['stable']:
                    ret['stable'][count].append((c.real, c.imag))
                else:
                    ret['stable'][count] = [(c.real, c.imag)]
            else:
                if count in ret['unstable']:
                    ret['unstable'][count].append((c.real, c.imag))
                else:
                    ret['unstable'][count] = [(c.real, c.imag)]
        pool.close()
        pool.join()
    return ret


def main():
    result = get_fractal((-2.5, 1.3), 10000)
    plt.figure(figsize=(128, 128))
    cmap = plt.get_cmap('jet')
    for orbit in result['stable']:
        plt.scatter(*zip(*result['stable'][orbit]), color='black', s=0.1)
    for orbit in result['unstable']:
        plt.scatter(*zip(*result['unstable'][orbit]), color=cmap(orbit), s=0.1)
    plt.savefig('temp.png')


if __name__ == '__main__':
    mp.freeze_support()
    main()
