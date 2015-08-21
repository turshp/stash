#!/usr/bin/env python
import sys
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost', port=32769))
channel = connection.channel()

channel.queue_declare(queue='hello')

message = ''.join(sys.argv[1:]) or "Hello, RabbitMQ"
channel.basic_publish(exchange='',
                      routing_key='hello',
                      body=message)

print " [x] Sent %r" % message

connection.close()

