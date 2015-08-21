# /usr/bin/env python
# -*- coding: utf-8 -*-

from sqlalchemy import Column, String, Integer, Float, create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.schema import ForeignKey

# 创建对象的基类:
Base = declarative_base()

class User(Base):
    __tablename__ = 'user'

    id = Column(Integer, primary_key=True)
    name = Column(String(20))
    sex = Column(Integer)
    degree = Column(Float(16,2))
    # 一对多:
    books = relationship('Book')

    def __repr__(self):
        return "<User %r, name %r, sex %r, degree %r, books %r>" \
               % (self.id, self.name, self.sex, self.degree, self.books)


class Book(Base):
    __tablename__ = 'book'

    id = Column(Integer, primary_key=True)
    name = Column(String(20))
    # “多”的一方的book表是通过外键关联到user表的:
    user_id = Column(Integer, ForeignKey('user.id'))

    def __repr__(self):
        return "<Book %r, name %r, user_id %r>" \
               % (self.id, self.name, self.user_id)


# 初始化数据库连接:
engine = create_engine('mysql+mysqlconnector://root:pica8@localhost:32768/test', echo=True)
# 创建DBSession类型:
DBSession = sessionmaker(bind=engine)

# 创建session对象:
#session = DBSession()
# 创建新User对象:
#new_user = User(name='Bob', sex = 0, degree = 55.5)
# 添加到session:
#session.add(new_user)
# 提交即保存到数据库:
#session.commit()
# 关闭session:
#session.close()

# 创建Session:
session = DBSession()
# 创建Query查询，filter是where条件，最后调用one()返回唯一行，如果调用all()则返回所有行:
user = session.query(User).first()
book = user.books[0]
book.name = "C++ primer v4"
# 打印类型和对象的name属性:
print user
session.add(user)
session.commit()
# 关闭Session:
session.close()


