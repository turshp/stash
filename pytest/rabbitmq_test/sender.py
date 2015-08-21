#!/usr/bin/env python
import pika

connection = pika.BlockingConnection(pika.ConnectionParameters(
        host='localhost', port=32768))
channel = connection.channel()

channel.queue_declare(queue='hello')

for i in range(100):
    msg = "Hello, RabbitMQ %s." % i
    channel.basic_publish(exchange='',
                          routing_key='hello',
                          body=msg)
    print msg

connection.close()

