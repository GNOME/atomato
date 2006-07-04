#!/usr/bin/env python

import dbus
import dbus.service
import dbus.glib
import gobject
import Image
import ImageFilter

class Image(dbus.service.Object):
    def __init__(self, bus_name, object_path="/image"):
        dbus.service.Object.__init__(self, bus_name, object_path)

    @dbus.service.method("org.gnome.atomato.image", in_signature="ss")
    def transform_image_format (self, image_in_path, image_out_path):
        try:
            Image.open(image_in_path).save(image_out_path)
        except IOError:
            return 1
        return 0

    @dbus.service.method("org.gnome.atomato.image", in_signature="ssii")
    def create_thumbnail (self, image_in_path, image_out_path, h, v):
        try:
            Image.open(image_in_path).thumbnail((h,v)).save(image_out_path)
        except IOError:
            return 1
        return 0

    @dbus.service.method("org.gnome.atomato.image", in_signature="ssii")
    def crop_image (self, image_in_path, image_out_path, h, v):
        try:
            Image.open(image_in_path).crop((h,v)).save(image_out_path)
        except IOError:
            return 1
        return 0

    @dbus.service.method("org.gnome.atomato.image", in_signature="ssii")
    def resize_image (self, image_in_path, image_out_path, h, v):
        try:
            Image.open(image_in_path).resize((h,v)).save(image_out_path)
        except IOError:
            return 1
        return 0

    @dbus.service.method("org.gnome.atomato.image", in_signature="ssi")
    def rotate_image (self, image_in_path, image_out_path, degrees):
        try:
            Image.open(image_in_path).rotate(degrees).save(image_out_path)
        except IOError:
            return 1
        return 0

    @dbus.service.method("org.gnome.atomato.image", in_signature="ss")
    def flip_left_right (self, image_in_path, image_out_path):
        try:
            Image.open(image_in_path).transpose(Image.FLIP_LEFT_RIGHT).save(image_out_path)
        except IOError:
            return 1
        return 0

    @dbus.service.method("org.gnome.atomato.image", in_signature="ss")
    def flip_top_down (self, image_in_path, image_out_path):
        try:
            Image.open(image_in_path).transpose(Image.FLIP_TOP_BOTTOM).save(image_out_path)
        except IOError:
            return 1
        return 0

session_bus = dbus.SessionBus()
name = dbus.service.BusName("org.gnome.atomato.image", bus=session_bus)
object = Image(name)

mainloop = gobject.MainLoop()
mainloop.run()

