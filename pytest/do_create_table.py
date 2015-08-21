"""pica8-mechanism driver

Revision ID: 1bf82cc705c5
Revises: 034883111f
Create Date: 2015-05-15 10:09:23.363893

"""

# revision identifiers, used by Alembic.
revision = '1bf82cc705c5'
down_revision = '034883111f'

from alembic import op
import sqlalchemy as sa
from sqlalchemy.dialects import mysql


def upgrade():
    op.create_table(
        'pica8_interfaces',
        sa.Column('id', sa.String(length=36), nullable=False,
                  primary_key=True),
        sa.Column('switch', sa.String(length=36), nullable=False),
        sa.Column('interface', sa.String(10), nullable=False)
    )

    op.create_table(
        'pica8_vlan_allocations',
        sa.Column('id', sa.String(length=36), nullable=False,
                  primary_key=True),
        sa.Column('tenant_id', sa.String(length=255), nullable=False),
        sa.Column('network_id', sa.String(length=36), nullable=False),
        sa.Column('segmentation_id', sa.Integer, nullable=False),
        sa.Column('vlan_id', sa.Integer, nullable=False),
        sa.Column('vm_reference', sa.Integer, nullable=False, default=0),
        sa.Column('interface_id', sa.String(length=36), nullable=True),
        sa.ForeignKeyConstraint(['interface_id'], ['pica8_interfaces.id'],
                                ondelete='SET NULL')
    )


def downgrade():
    op.drop_table('pica8_interfaces')
    op.drop_table('pica8_vlan_allocations')
