/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -p chronosVideoInterface ../ca.krontech.chronos.video.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef CHRONOSVIDEOINTERFACE_H_1518199313
#define CHRONOSVIDEOINTERFACE_H_1518199313

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface ca.krontech.chronos.video
 */
class CaKrontechChronosVideoInterface: public QDBusAbstractInterface
{
	Q_OBJECT
public:
	static inline const char *staticInterfaceName()
	{ return "ca.krontech.chronos.video"; }

public:
	CaKrontechChronosVideoInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

	~CaKrontechChronosVideoInterface();

public Q_SLOTS: // METHODS
	inline QDBusPendingReply<> livestream(const QVariantMap &settings)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(settings);
		return asyncCallWithArgumentList(QLatin1String("livestream"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> playback(const QVariantMap &args)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(args);
		return asyncCallWithArgumentList(QLatin1String("playback"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> livedisplay(const QVariantMap &args)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(args);
		return asyncCallWithArgumentList(QLatin1String("livedisplay"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> liverecord(const QVariantMap &args)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(args);
		return asyncCallWithArgumentList(QLatin1String("liverecord"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> configure(const QVariantMap &settings)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(settings);
		return asyncCallWithArgumentList(QLatin1String("configure"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> recordfile(const QVariantMap &settings)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(settings);
		return asyncCallWithArgumentList(QLatin1String("recordfile"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> overlay(const QVariantMap &settings)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(settings);
		return asyncCallWithArgumentList(QLatin1String("overlay"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> reset()
	{
		QList<QVariant> argumentList;
		return asyncCallWithArgumentList(QLatin1String("pause"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> pause()
	{
		QList<QVariant> argumentList;
		return asyncCallWithArgumentList(QLatin1String("pause"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> stop()
	{
		QList<QVariant> argumentList;
		return asyncCallWithArgumentList(QLatin1String("stop"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> flush()
	{
		QList<QVariant> argumentList;
		return asyncCallWithArgumentList(QLatin1String("flush"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> status()
	{
		QList<QVariant> argumentList;
		return asyncCallWithArgumentList(QLatin1String("status"), argumentList);
	}

	inline QDBusPendingReply<QVariantMap> set(const QVariantMap &values)
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue(values);
		return asyncCallWithArgumentList(QLatin1String("set"), argumentList);
	}
};

namespace com {
	namespace krontech {
		namespace chronos {
			typedef ::CaKrontechChronosVideoInterface video;
		}
	}
}
#endif
