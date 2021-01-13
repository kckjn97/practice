import sqlalchemy as sa
from sqlalchemy.ext.declarative import declarative_base

Base = sa.ext.declarative.declarative_base()
class User(Base):
	__tablename__ = 'users'
	id = sa.Column(sa.Integer, sa.Sequence('user_id_seq'), primary_key=True)
	name = sa.Column(sa.String)
	fullname = sa.Column(sa.String)
	nickname = sa.Column(sa.String)

	def __repr__(self):
		return "<User(name='%s', fullname='%s', nickname='%s')>" % (self.name, self.fullname, self.nickname)

engine = sa.create_engine('sqlite:///sqlite.db', echo=False)
Base.metadata.create_all(engine)
Session = sa.orm.sessionmaker(bind=engine)
session = Session()

user1 = User(name='Lee', fullname='Lee Eunjae', nickname='ej')
user2 = User(name='Kim', fullname='Kim Junghyun', nickname='kjh')
user3 = User(name='Lim', fullname='Lim Keunhak', nickname='lkh')
user4 = User(name='Kim', fullname='Kim Dohyung', nickname='kdh')
session.add(user1)
session.add_all([user2, user3, user4])
session.commit()

for user in session.query(User).filter(User.name == 'Kim'):
	print(user.id, user.fullname)
print('-----------------------')

session.query(User).filter_by(name='Kim').delete()
session.commit()

for instance in session.query(User).order_by(User.id):
	print(instance)

session.close()
