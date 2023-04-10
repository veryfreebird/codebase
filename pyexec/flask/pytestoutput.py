import pytest
from datetime import datetime


def test_add():
    assert 1 == 2


def gen_report_name():
    prefix = '测试报告'
    ts = datetime.now().strftime('%Y-%m-%d-%H-%M-%S')
    return prefix + ts + '.html'


if __name__ == '__main__':
    report_name = gen_report_name()
    pytest.main([f'--html=output/{report_name}'])